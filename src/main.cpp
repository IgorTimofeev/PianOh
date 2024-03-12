#include <Arduino.h>
#include <Wire.h>


#include <string>
#include "piano/piano.h"
#include "map"
#include "piano/particles/flame_particle.h"
#include "HardwareSerial.h"
#include "piano/effects/flame_effect.h"
#include "piano/effects/rainbow_effect.h"
#include "piano/effects/water_effect.h"
#include "piano/effects/test_effect.h"
#include "piano/effects/gradient_effect.h"
#include "piano/effects/strobe_effect.h"
#include "grafica/color.h"
#include "grafica/number.h"
#include "grafica/elements/stack_layout.h"
#include "grafica/elements/text.h"
#include "grafica/elements/rectangle.h"
#include "grafica/elements/circle.h"
#include "grafica/elements/slider.h"
#include "grafica/elements/seven_segment.h"
#include "grafica/elements/tab_bar.h"
#include "grafica/tft_display.h"
#include "ui/tabs.h"

using namespace grafica;

// -------------------------------------------------------------------------------

#define LED_ONBOARD_PIN1 12
#define LED_ONBOARD_PIN2 13
#define LED_ONBOARD_BLINK_PIN LED_ONBOARD_PIN1

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
	auto gradient = new LinearGradient();
	gradient->getStops().emplace_back(0, Color(0xFF, 0x00, 0x00));
	gradient->getStops().emplace_back(0.5, Color(0x00, 0xFF, 0x00));
	gradient->getStops().emplace_back(1, Color(0x00, 0x00, 0xFF));

	changeEffect(new GradientEffect(gradient));
}

// ---------------------------------- Display ----------------------------------

TFTDisplay display = TFTDisplay(4, 5, 9, 8);

uint32_t displayRenderDeadline = 0;

void displayRender() {
	if (micros() <= displayRenderDeadline)
		return;

	display.readTouch();
	display.render();

	displayRenderDeadline = micros() + 1000000 / 30;
}


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

void setup() {
	// Onboard LED
	pinMode(LED_ONBOARD_PIN1, OUTPUT);
	pinMode(LED_ONBOARD_PIN2, OUTPUT);

	digitalWrite(LED_ONBOARD_PIN2, HIGH);

	// Display
	display.begin();
	display.getWorkspace().addChild(new ui::PianoTabBar());

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