#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "fonts/Org_01.h"
#include <string>
#include "color.h"
#include "piano/piano.h"
#include "map"
#include "piano/particles/flame_particle.h"
#include "HardwareSerial.h"
#include "number.h"
#include "piano/effects/flame_effect.h"
#include "piano/effects/rainbow_effect.h"
#include "piano/effects/water_effect.h"
#include "piano/effects/test_effect.h"

// -------------------------------------------------------------------------------

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define LED_ONBOARD_PIN1 12
#define LED_ONBOARD_PIN2 13
#define LED_ONBOARD_BLINK_PIN LED_ONBOARD_PIN1

#define PIANO_KEY_WIDTH 3
#define PIANO_KEY_WHITE_HEIGHT 20
#define PIANO_KEY_BLACK_HEIGHT 12

// ---------------------------------- Piano ----------------------------------

Piano piano = Piano(88, 180, 18);

std::map<uint16_t, uint8_t> pressedKeysVelocities;

uint32_t pianoRenderDeadline;

void renderPianoStrip() {
	uint32_t time = millis();

	if (time <= pianoRenderDeadline)
		return;

	// Updating piano
	piano.renderStrip(time);

	pianoRenderDeadline = time + 1000 / 60;
}

uint8_t getKeyVelocity(uint16_t index) {
	auto kayAndVelocity = pressedKeysVelocities.find(index);

	return kayAndVelocity == pressedKeysVelocities.end() ? 0 : kayAndVelocity->second;
}

// ---------------------------------- Display ----------------------------------

uint32_t displayRenderDeadline = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void displayDrawWhiteKey(int16_t &x, int16_t &y, uint8_t &keyIndex) {
	display.fillRect(
		x,
		y,
		PIANO_KEY_WIDTH,
		PIANO_KEY_WHITE_HEIGHT,
		getKeyVelocity(keyIndex) > 0 ? BLACK : WHITE
	);

	x += PIANO_KEY_WIDTH + 1;
}

void displayDrawBlackKey(int16_t &x, int16_t &y, uint8_t &keyIndex) {
	display.fillRect(
		x,
		y,
		PIANO_KEY_WIDTH,
		PIANO_KEY_BLACK_HEIGHT,
		getKeyVelocity(keyIndex) > 0 ? WHITE : BLACK
	);

	x += PIANO_KEY_WIDTH + 1;
}

void displayDrawOctave(int16_t &x, int16_t &y, uint8_t &keyIndex) {
	// White
	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 1;
	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
	displayDrawWhiteKey(x, y, keyIndex); keyIndex -= 10;
	x -= (PIANO_KEY_WIDTH + 1) * 6 + 2;

	// Black
	displayDrawBlackKey(x, y, keyIndex); keyIndex += 2;
	displayDrawBlackKey(x, y, keyIndex); keyIndex += 3;
	x += PIANO_KEY_WIDTH + 1;
	
	displayDrawBlackKey(x, y, keyIndex); keyIndex += 2;
	displayDrawBlackKey(x, y, keyIndex); keyIndex += 2;
	displayDrawBlackKey(x, y, keyIndex); keyIndex += 2;
	x += 2;
}

void displayDrawOctaves() {
	int16_t x = 0;
	int16_t y = SCREEN_HEIGHT - PIANO_KEY_WHITE_HEIGHT;
	uint8_t keyIndex = 0; 

	// 0 octave

	// White
	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
	displayDrawWhiteKey(x, y, keyIndex); keyIndex -= 1;
	x -= (PIANO_KEY_WIDTH + 1) + 2;

	// Black
	displayDrawBlackKey(x, y, keyIndex); keyIndex += 2;

	// 7 octaves
	for (int i = 0; i < 7; i++)
		displayDrawOctave(x, y, keyIndex);
}

MidiEvent lastMidiEvent;

void renderMidiEventOnDisplay() {
	if (millis() < displayRenderDeadline)
		return;

	display.clearDisplay();

	displayDrawOctaves();

	display.setCursor(0, 5);
	display.print("MIDI ");
	display.print(String((int) lastMidiEvent.data1));
	display.print(" ");
	display.print(String((int) lastMidiEvent.channel));
	display.print(" ");
	display.print(String((int) lastMidiEvent.data1));
	display.print(" ");
	display.print(String((int) lastMidiEvent.data2));

	display.display();

	displayRenderDeadline = millis() + 10;
}

// ---------------------------------- Onboard LED ----------------------------------

uint32_t onboardLEDBlinkDeadline = 0;

void onboardLEDBlink() {
	if (onboardLEDBlinkDeadline > 0)
		return;

	digitalWrite(LED_ONBOARD_BLINK_PIN, HIGH);
	onboardLEDBlinkDeadline = millis() + 5;
}

void updateOnboardLED() {
	if (onboardLEDBlinkDeadline == 0 || millis() <= onboardLEDBlinkDeadline)
		return;

	digitalWrite(LED_ONBOARD_BLINK_PIN, LOW);
	onboardLEDBlinkDeadline = 0;
}

// ---------------------------------- Penis ----------------------------------

void setup() {
	// Onboard LED
	pinMode(LED_ONBOARD_PIN1, OUTPUT);
	pinMode(LED_ONBOARD_PIN2, OUTPUT);

	digitalWrite(LED_ONBOARD_PIN2, HIGH);

	// Display
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
		return;

	display.clearDisplay();
	display.setFont(&Org_01);
	display.setTextColor(WHITE);

	// Piano
	piano.begin(115200);
	piano.clearStrip();
	piano.setEffect(new RainbowEffect());

	piano.addOnMidiRead([](MidiEvent& event) {
		switch (event.type) {
			case MidiEventType::NoteOn:
				pressedKeysVelocities[Piano::noteToKey(event.data1)] = event.data2;

				switch (Piano::noteToKey(event.data1)) {
					case 84:
						piano.setEffect(new WaterEffect());
						break;

					case 85:
						piano.setEffect(new RainbowEffect());
						break;

					case 86:
						piano.setEffect(new FlameEffect);
						break;

					case 87:
						piano.setEffect(new TestEffect(Color(255, 0, 0)));
						break;
				}

				break;

			case MidiEventType::NoteOff:
				pressedKeysVelocities.erase(Piano::noteToKey(event.data1));
				break;

			case MidiEventType::ControlChange:
				switch (event.data1) {
					// Vertical
					case 71:
						piano.setStripBrightness(Number::clampUint8(event.data2 * 2));
						break;

//					// Horizontal
//					case 74:
//						auto color = Color(Color::gold);
//						color.multiply((float) MIDI.getData2() / 127.0f);
//						pianoFiller->color = color;
//
//						break;
				}

				break;

			default:
				break;
		}

		onboardLEDBlink();

		lastMidiEvent = event;
	});
}

void loop() {
	piano.readMidiEvents();

	renderPianoStrip();
	renderMidiEventOnDisplay();
	updateOnboardLED();
}