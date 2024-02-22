#include "piano/piano.h"
#include "piano/particles/particle.h"
#include "piano/effects/flame_effect.h"
#include "color.h"

Piano::Piano(uint8_t keysCount, uint16_t stripLEDCount, int16_t stripPin) :
	keysCount(keysCount)
{
	strip = Adafruit_NeoPixel(stripLEDCount, stripPin, NEO_GRB + NEO_KHZ800);
}

Piano::~Piano() {
	delete effect;
}

uint16_t Piano::getStripLength() {
	return strip.numPixels();
}

void Piano::invertStripIndexIfRequired(uint16_t& index) {
	if (isStripInverted)
		index = getStripLength() - index - 1;
}

bool Piano::isStripIndexInRange(uint16_t index) {
	return index >= 0 && index < getStripLength();
}

uint8_t Piano::getStripBrightness() {
	return strip.getBrightness();
}

void Piano::setStripBrightness(uint8_t value) {
	strip.setBrightness(value);
}

Color Piano::getStripColor(uint16_t index) {
	if (!isStripIndexInRange(index))
		return Color::black;

	invertStripIndexIfRequired(index);

	return Color(strip.getPixelColor(index));
}

void Piano::setStripColor(uint16_t index, const Color& value) {
	if (!isStripIndexInRange(index))
		return;

	invertStripIndexIfRequired(index);

	strip.setPixelColor(index, value.r, value.g, value.b);
}

void Piano::begin(uint32_t stripBaudRate) {
	Serial.begin(stripBaudRate);
	strip.begin();
}

void Piano::updateStrip() {
	strip.show();
}

void Piano::renderStrip(const uint32_t& time) {
	if (effect) {
		effect->render(*this, time);
	}
	else {
		clearStrip();
	}

	updateStrip();
}

void Piano::clearStrip() {
	strip.clear();
}

void Piano::fillStrip(uint16_t from, uint16_t to, Color& color) {
	invertStripIndexIfRequired(from);
	invertStripIndexIfRequired(to);

	strip.fill(color.toUint32(), from, to);
}

void Piano::fillStrip(Color& color) {
	fillStrip(0, getStripLength() - 1, color);
}

void Piano::readMidiEvents() {
	if (Serial.available() == 0)
		return;

	const int bufferLength = 64;
	uint8_t buffer[bufferLength];

	MidiEvent event;

	while (Serial.available() > 0) {
		auto bytesRead = Serial.read(buffer, Serial.available());

		if (bytesRead == 0)
			break;

		int index = 0;
		while (index < bytesRead) {
			event = MidiEvent::fromByteBuffer(buffer, index);

			for (const auto& callback : onMidiRead) {
				callback(event);
			}

			if (effect)
				effect->handleEvent(*this, event);
		}
	}
}

void Piano::addOnMidiRead(const std::function<void(MidiEvent&)> &callback) {
	onMidiRead.push_back(callback);
}

uint16_t Piano::noteToKey(uint8_t note) {
	return note - Piano::midiKeyMinimum;
}

uint16_t Piano::keyToStripIndex(uint16_t key) {
	return (uint16_t) ((float) key / (float) keysCount * (float) getStripLength());
}

uint16_t Piano::noteToStripIndex(uint8_t note) {
	return keyToStripIndex(noteToKey(note));
}
