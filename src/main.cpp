#include <Arduino.h>
#include <Wire.h>
#include <Midi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "fonts/Org_01.h"
#include <string>
#include "color.h"
#include "piano/piano.h"
#include "map"
#include "piano/particles/flame_particle.h"
#include "random.h"
#include "HardwareSerial.h"
#include "number.h"
#include "piano/effects/golden_effect.h"
#include "piano/effects/rainbow_effect.h"

using Random = effolkronium::random_static;

// -------------------------------------------------------------------------------

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define LED_ONBOARD_PIN1 12
#define LED_ONBOARD_PIN2 13
#define LED_ONBOARD_BLINK_PIN LED_ONBOARD_PIN1
#define LED_ONBOARD_BLINK_TIMEOUT 5

#define PIANO_KEY_WIDTH 3
#define PIANO_KEY_WHITE_HEIGHT 20
#define PIANO_KEY_BLACK_HEIGHT 12

// ---------------------------------- Piano ----------------------------------

Piano piano = Piano(88, 180, 18);

unsigned long pianoRenderDeadline;

void renderPiano() {
	if (millis() <= pianoRenderDeadline)
		return;

	// Updating piano
	piano.renderStrip();

	pianoRenderDeadline = millis() + 1000 / 60;
}

// ---------------------------------- Display ----------------------------------

unsigned long displayRenderDeadline = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void displayDrawWhiteKey(int16_t &x, int16_t &y, uint8_t &keyIndex) {
	display.fillRect(
		x,
		y,
		PIANO_KEY_WIDTH,
		PIANO_KEY_WHITE_HEIGHT,
		piano.getKeyVelocity(keyIndex) > 0 ? BLACK : WHITE
	);

	x += PIANO_KEY_WIDTH + 1;
}

void displayDrawBlackKey(int16_t &x, int16_t &y, uint8_t &keyIndex) {
	display.fillRect(
		x,
		y,
		PIANO_KEY_WIDTH,
		PIANO_KEY_BLACK_HEIGHT,
		piano.getKeyVelocity(keyIndex) > 0 ? WHITE : BLACK
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

void displayClear() {
	display.clearDisplay();

	displayDrawOctaves();

	display.setCursor(0, 5);	
}

// ---------------------------------- Onboard LED ----------------------------------

unsigned long onboardLEDBlinkDeadline = 0;

void onboardLEDBlink() {
	if (onboardLEDBlinkDeadline > 0)
		return;

	digitalWrite(LED_ONBOARD_BLINK_PIN, HIGH);
	onboardLEDBlinkDeadline = millis() + LED_ONBOARD_BLINK_TIMEOUT;
}

void updateOnboardLED() {
	if (onboardLEDBlinkDeadline == 0 || millis() <= onboardLEDBlinkDeadline)
		return;

	digitalWrite(LED_ONBOARD_BLINK_PIN, LOW);
	onboardLEDBlinkDeadline = 0;
}

void renderMidiEventOnDisplay(const MidiEvent& event) {
	if (millis() < displayRenderDeadline)
		return;

	displayClear();

	display.print("MIDI ");
	display.print(String((int) event.data1));
	display.print(" ");
	display.print(String((int) event.channel));
	display.print(" ");
	display.print(String((int) event.data1));
	display.print(" ");
	display.print(String((int) event.data2));

	display.display();

	displayRenderDeadline = millis() + 10;
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

	display.setFont(&Org_01);
	display.setTextColor(WHITE);

	displayClear();
	display.print("Ready");
	display.display();

	// Piano
	piano.begin();
	piano.clearStrip();
//	piano.effect = new GoldenEffect();
	piano.effect = new RainbowEffect();

	piano.addOnMidiRead([](const MidiEvent& event) {
		switch (event.type) {
			case midi::ControlChange:
				switch (event.data1) {
					// Vertical
					case 71:
						piano.setStripBrightness(event.data2);
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

		renderMidiEventOnDisplay(event);
		onboardLEDBlink();
	});
}

void loop() {
	piano.readMidi();

	renderPiano();
	updateOnboardLED();
}