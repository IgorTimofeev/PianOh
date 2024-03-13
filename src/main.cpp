#include <Arduino.h>
#include <Wire.h>


#include <string>
#include "devices/piano/piano.h"
#include "map"
#include "HardwareSerial.h"
#include "devices/piano/effects/effect.h"
#include "devices/piano/effects/flame_effect.h"
#include "devices/piano/effects/rainbow_effect.h"
#include "devices/piano/effects/water_effect.h"
#include "devices/piano/effects/test_effect.h"
#include "devices/piano/effects/gradient_effect.h"
#include "devices/piano/effects/strobe_effect.h"
#include "grafica/color.h"
#include "grafica/number.h"
#include "grafica/display.h"
#include "ui/tabs/tabs.h"
#include "devices/piano/piano.h"

using namespace grafica;
using namespace devices::piano;

// -------------------------------------------------------------------------------

#define LED_ONBOARD_PIN1 12
#define LED_ONBOARD_PIN2 13
#define LED_ONBOARD_BLINK_PIN LED_ONBOARD_PIN1

// ---------------------------------- Piano ----------------------------------

Piano piano = Piano(180, 18);

uint32_t pianoRenderDeadline;

void renderPianoStrip() {
	uint32_t time = millis();

	if (time <= pianoRenderDeadline)
		return;

	// Updating piano
	piano.renderStrip(time);

	pianoRenderDeadline = time + 1000 / 60;
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

Display display = Display(4, 5, 9, 8);

uint32_t displayRenderDeadline = 0;

void displayRender() {
	if (micros() <= displayRenderDeadline)
		return;

	display.readTouch();
	display.render();

	displayRenderDeadline = micros() + 1000000 / 30;
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
	display.getWorkspace().addChild(new ui::TabBar());

	// Piano
	piano.begin();
	piano.clearStrip();
	changeEffect(new RainbowEffect());

	piano.addOnMidiRead([](MidiEvent& event) {
		switch (event.type) {
			case MidiType::NoteOn:
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

			case MidiType::ControlChange:
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
	});
}

void loop() {
	displayRender();

	piano.readMidiEvents();
	renderPianoStrip();

	updateOnboardLED();
}