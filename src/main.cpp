#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "fonts/Org_01.h"
#include <string>
#include "strip.h"
#include "map"
#include "particles/particle.h"
#include "particles/flame.h"
#include "random.hpp"
#include "number.h"

using Random = effolkronium::random_static;

// -------------------------------------------------------------------------------

#define SERIAL_BUFFER_SIZE 128

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define LED_ONBOARD_PIN1 12
#define LED_ONBOARD_PIN2 13
#define LED_ONBOARD_BLINK_PIN LED_ONBOARD_PIN1
#define LED_ONBOARD_BLINK_TIMEOUT 5

#define LED_STRIP_PIN 18
#define LED_STRIP_LENGTH 180

#define PIANO_KEY_VELOCITY_FACTOR 1.0
#define PIANO_KEY_MIN 21
#define PIANO_KEY_TOTAL 88
#define PIANO_KEY_WIDTH 3
#define PIANO_KEY_WHITE_HEIGHT 20
#define PIANO_KEY_BLACK_HEIGHT 12

// ---------------------------------- Piano ----------------------------------

float pianoKeysVelocities[PIANO_KEY_TOTAL];

// ---------------------------------- Display ----------------------------------

unsigned long displayRenderDeadline = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void displayDrawWhiteKey(int16_t &x, int16_t &y, uint8_t &keyIndex) {
	display.fillRect(
		x,
		y,
		PIANO_KEY_WIDTH,
		PIANO_KEY_WHITE_HEIGHT,
		pianoKeysVelocities[keyIndex] > 0 ? BLACK : WHITE
	);

	x += PIANO_KEY_WIDTH + 1;
}

void displayDrawBlackKey(int16_t &x, int16_t &y, uint8_t &keyIndex) {
	display.fillRect(
		x,
		y,
		PIANO_KEY_WIDTH,
		PIANO_KEY_BLACK_HEIGHT,
		pianoKeysVelocities[keyIndex] > 0 ? WHITE : BLACK
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

void displayRender() {
	if (millis() <= displayRenderDeadline)
		return;

	display.display();
	displayRenderDeadline = millis() + 10;
}

// ---------------------------------- Onboard LED ----------------------------------

unsigned long onboardLEDBlinkDeadline = 0;

void onboardLEDBlink() {
	if (onboardLEDBlinkDeadline > 0)
		return;

	digitalWrite(LED_ONBOARD_BLINK_PIN, HIGH);
	onboardLEDBlinkDeadline = millis() + LED_ONBOARD_BLINK_TIMEOUT;
}

void LEDOnboardUpdate() {
	if (onboardLEDBlinkDeadline == 0 || millis() <= onboardLEDBlinkDeadline)
		return;

	digitalWrite(LED_ONBOARD_BLINK_PIN, LOW);
	onboardLEDBlinkDeadline = 0;
}

// ---------------------------------- LED strip ----------------------------------

Strip strip = Strip(LED_STRIP_LENGTH, LED_STRIP_PIN);

unsigned long stripUpdateDeadline;
unsigned long stripRenderDeadline;

int PianoNoteToKeyIndex(int note) {
	return note - PIANO_KEY_MIN;
}

int PianoKeyIndexToStripIndex(int index) {
	return (int) ((float) (PIANO_KEY_TOTAL - index - 1) / PIANO_KEY_TOTAL * strip.getLength());
}

std::map<int, FlameParticle*> pianoKeysParticles;

void stripNoteOn(int note, uint8_t velocity) {
	float floatVelocity = (float) velocity / 127 * PIANO_KEY_VELOCITY_FACTOR;

	if (floatVelocity > 1)
		floatVelocity = 1;

	auto index = PianoNoteToKeyIndex(note);

	pianoKeysVelocities[index] = floatVelocity;

	auto particle = new FlameParticle();
	particle->position = ((float) (PIANO_KEY_TOTAL - index) / PIANO_KEY_TOTAL) * strip.getLength();
	particle->sizeLeft = 5;
	particle->sizeRight = 5;

	particle->brightness = floatVelocity;
	particle->brightnessMaximum = particle->brightness;
	particle->brightnessMinimum = particle->brightness * 0.4f;
	particle->brightnessLeft = 0.1;
	particle->brightnessRight = 0.1;

	particle->life = 0;
	particle->lifeVector = 0.2;

	pianoKeysParticles[index] = particle;

	strip.addParticle(particle);
}

void stripNoteOff(int note) {
	auto index = PianoNoteToKeyIndex(note);
	
	pianoKeysVelocities[index] = 0;

	FlameParticle* particle = pianoKeysParticles[index];
	particle->lifeVector = -0.09;
	pianoKeysParticles.erase(index);
}

void stripSpawnSparks() {
	const float bigOffset = 6;
	const float smallOffset = 4;

	bool isLeft;
	float isLeftFactor;
	FlameParticle* particle;

	for (auto keyAndParticle : pianoKeysParticles) {
		if (!Random::get<bool>(0.2))
			continue;

		isLeft = Random::get<bool>() == 1;
		isLeftFactor = isLeft ? -1.0f : 1.0f;

		particle = new FlameParticle();
		particle->position = keyAndParticle.second->position + isLeftFactor;
		particle->positionVector = isLeftFactor * Random::get(0.3f, 0.9f);
		particle->sizeLeft = isLeft ? bigOffset : smallOffset;
		particle->sizeRight = isLeft ? smallOffset : bigOffset;

		particle->brightness = keyAndParticle.second->brightnessMaximum * Random::get(0.1f, 0.3f);
		particle->brightnessMaximum = particle->brightness;
		particle->brightnessMinimum = particle->brightness * 0.4f;
		particle->brightnessLeft = isLeft ? 0.2 : 0.1;
		particle->brightnessRight = isLeft ? 0.1 : 0.2;

		particle->life = 1;
		particle->lifeVector = Random::get(-0.04f, -0.12f);

		strip.addParticle(particle);
	}
}

void stripRender() {
	if (millis() <= stripRenderDeadline)
		return;

	// Updating strip
	strip.render();

	// Spawning sparks
	stripSpawnSparks();

	stripRenderDeadline = millis() + 1000 / 60;
}

// ---------------------------------- Serial ----------------------------------

char serialBuffer[SERIAL_BUFFER_SIZE];

void SerialRead() {
	auto available = Serial.available();

	if (available == 0)
		return;

	auto bytesRead = Serial.readBytes(serialBuffer, available);

	if (bytesRead == 0)
		return;

	for (int i = 0; i < bytesRead; i++) {
		switch (serialBuffer[i]) {
			// Note on
			case 144:
				stripNoteOn((int) serialBuffer[i + 1], (uint8_t) serialBuffer[i + 2]);
				i += 2;

				break;

			// Note off
			case 128:
				stripNoteOff((int) serialBuffer[i + 1]);
				i += 2;

				break;
		}	
	}

	// Printing data
	displayClear();

	display.print("MIDI");

	for (int i = 0; i < bytesRead; i++) {
		display.print(" ");
		display.print((int) serialBuffer[i]);
	}

	// Blink!
	onboardLEDBlink();
}

// ---------------------------------- Penis ----------------------------------

void setup() {
	Serial.begin(115200);

	// Onboard LEDs
	pinMode(LED_ONBOARD_PIN1, OUTPUT);
	pinMode(LED_ONBOARD_PIN2, OUTPUT);

	digitalWrite(LED_ONBOARD_PIN2, HIGH);

	// LED strip
	strip.begin();

	// Display
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
		return;

	display.setFont(&Org_01);
	display.setTextColor(WHITE);

	displayClear();
	display.print("Ready");
}

void loop() {
	SerialRead();

	stripRender();

	LEDOnboardUpdate();
	displayRender();
}