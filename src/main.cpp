#include <Arduino.h>
#include <Wire.h>


#include <string>
#include "ui/color.h"
#include "piano/piano.h"
#include "map"
#include "piano/particles/flame_particle.h"
#include "HardwareSerial.h"
#include "number.h"
#include "piano/effects/flame_effect.h"
#include "piano/effects/rainbow_effect.h"
#include "piano/effects/water_effect.h"
#include "piano/effects/test_effect.h"
#include "piano/effects/gradient_effect.h"
#include "piano/effects/strobe_effect.h"
#include "ui/elements/workspace.h"
#include "ui/elements/stack_layout.h"
#include "ui/elements/text.h"
#include "ui/elements/rectangle.h"
#include "ui/elements/circle.h"
#include "ui/elements/slider.h"
#include "ui/elements/seven_segment.h"
#include "ui/elements/tab_bar.h"
#include "tabs.h"

using namespace ui;

// -------------------------------------------------------------------------------

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

void changeEffect(Effect* effect) {
	delete piano.getEffect();

	piano.setEffect(effect);
}

void setGradientEffect() {
	changeEffect(new GradientEffect(new LinearGradient(std::vector<GradientStep*> {
		new GradientStep(0, Color(0xFF, 0x00, 0x00)),
		new GradientStep(0.5, Color(0x00, 0xFF, 0x00)),
		new GradientStep(1, Color(0x00, 0x00, 0xFF))
	})));
}

// ---------------------------------- Display ----------------------------------

TFTDisplay display = TFTDisplay();

uint32_t displayRenderDeadline = 0;

void displayRender() {
	if (micros() <= displayRenderDeadline)
		return;

	display.readTouch();
	display.render();

	displayRenderDeadline = micros() + 1000000 / 30;
}

//void displayDrawWhiteKey(int16_t &x, int16_t &y, uint8_t &keyIndex) {
//	adafruitDisplay.fillRect(
//		x,
//		y,
//		PIANO_KEY_WIDTH,
//		PIANO_KEY_WHITE_HEIGHT,
//		getKeyVelocity(keyIndex) > 0 ? BLACK : WHITE
//	);
//
//	x += PIANO_KEY_WIDTH + 1;
//}
//
//void displayDrawBlackKey(int16_t &x, int16_t &y, uint8_t &keyIndex) {
//	adafruitDisplay.fillRect(
//		x,
//		y,
//		PIANO_KEY_WIDTH,
//		PIANO_KEY_BLACK_HEIGHT,
//		getKeyVelocity(keyIndex) > 0 ? WHITE : BLACK
//	);
//
//	x += PIANO_KEY_WIDTH + 1;
//}
//
//void displayDrawOctave(int16_t &x, int16_t &y, uint8_t &keyIndex) {
//	// White
//	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
//	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
//	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 1;
//	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
//	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
//	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
//	displayDrawWhiteKey(x, y, keyIndex); keyIndex -= 10;
//	x -= (PIANO_KEY_WIDTH + 1) * 6 + 2;
//
//	// Black
//	displayDrawBlackKey(x, y, keyIndex); keyIndex += 2;
//	displayDrawBlackKey(x, y, keyIndex); keyIndex += 3;
//	x += PIANO_KEY_WIDTH + 1;
//
//	displayDrawBlackKey(x, y, keyIndex); keyIndex += 2;
//	displayDrawBlackKey(x, y, keyIndex); keyIndex += 2;
//	displayDrawBlackKey(x, y, keyIndex); keyIndex += 2;
//	x += 2;
//}
//
//void displayDrawOctaves() {
//	int16_t x = 0;
//	int16_t y = display.getSize().getHeight() - (int16_t) PIANO_KEY_WHITE_HEIGHT;
//	uint8_t keyIndex = 0;
//
//	// 0 octave
//
//	// White
//	displayDrawWhiteKey(x, y, keyIndex); keyIndex += 2;
//	displayDrawWhiteKey(x, y, keyIndex); keyIndex -= 1;
//	x -= (PIANO_KEY_WIDTH + 1) + 2;
//
//	// Black
//	displayDrawBlackKey(x, y, keyIndex); keyIndex += 2;
//
//	// 7 octaves
//	for (int i = 0; i < 7; i++)
//		displayDrawOctave(x, y, keyIndex);
//}

MidiEvent lastMidiEvent;

void renderMidiEventOnDisplay() {
//	adafruitDisplay.clearDisplay();
//
//	displayDrawOctaves();
//
//	adafruitDisplay.setCursor(0, 5);
//	adafruitDisplay.print("MIDI ");
//	adafruitDisplay.print(String((int) lastMidiEvent.data1));
//	adafruitDisplay.print(" ");
//	adafruitDisplay.print(String((int) lastMidiEvent.channel));
//	adafruitDisplay.print(" ");
//	adafruitDisplay.print(String((int) lastMidiEvent.data1));
//	adafruitDisplay.print(" ");
//	adafruitDisplay.print(String((int) lastMidiEvent.data2));
//
//	adafruitDisplay.display();
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

SevenSegment* sevenSegment;

void setup() {
	// Onboard LED
	pinMode(LED_ONBOARD_PIN1, OUTPUT);
	pinMode(LED_ONBOARD_PIN2, OUTPUT);

	digitalWrite(LED_ONBOARD_PIN2, HIGH);

	// Display
	display.begin();
	display.getWorkspace().addChild(new Rectangle(Color::black));
	display.getWorkspace().addChild(new PianoTabBar());

	// Piano
	piano.begin(115200);
	piano.clearStrip();
	changeEffect(new RainbowEffect());

	piano.addOnMidiRead([](MidiEvent& event) {
		switch (event.type) {
			case MidiEventType::NoteOn:
				pressedKeysVelocities[Piano::noteToKey(event.data1)] = event.data2;

				switch (Piano::noteToKey(event.data1)) {
					case 83:
						setGradientEffect();
						break;

					case 84:
						changeEffect(new WaterEffect());
						break;

					case 85:
						changeEffect(new RainbowEffect());
						break;

					case 86:
						changeEffect(new FlameEffect);
						break;

					case 87:
						changeEffect(new StrobeEffect(Color::white));
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
	displayRender();

	piano.readMidiEvents();
	renderPianoStrip();

	updateOnboardLED();
}