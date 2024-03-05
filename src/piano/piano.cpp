#include "piano/piano.h"
#include "piano/particles/particle.h"
#include "piano/effects/flame_effect.h"
#include "ui/color.h"

Piano::Piano(uint8_t keyCount, uint16_t stripLEDCount, int16_t stripPin) {
	_keyCount = keyCount;
	_strip = Adafruit_NeoPixel(stripLEDCount, stripPin, NEO_GRB + NEO_KHZ800);
}

Piano::~Piano() {
	delete _effect;
}

uint16_t Piano::getStripLength() {
	return _strip.numPixels();
}

void Piano::invertStripIndexIfRequired(uint16_t& index) {
	if (_isStripInverted)
		index = getStripLength() - index - 1;
}

bool Piano::isStripIndexInRange(uint16_t index) {
	return index >= 0 && index < getStripLength();
}

uint8_t Piano::getStripBrightness() {
	return _strip.getBrightness();
}

void Piano::setStripBrightness(uint8_t value) {
	_strip.setBrightness(value);
}

Color Piano::getStripColor(uint16_t index) {
	if (!isStripIndexInRange(index))
		return Color::black;

	invertStripIndexIfRequired(index);

	return Color(_strip.getPixelColor(index));
}

void Piano::setStripColor(uint16_t index, const Color& value) {
	if (!isStripIndexInRange(index))
		return;

	invertStripIndexIfRequired(index);

	_strip.setPixelColor(index, value.r, value.g, value.b);
}

void Piano::begin(uint32_t stripBaudRate) {
	Serial.begin(stripBaudRate);
	_strip.begin();
}

void Piano::renderStrip(const uint32_t& time) {
	if (_effect) {
		_effect->render(*this, time);
	}
	else {
		clearStrip();
	}

	_strip.show();
}

void Piano::clearStrip() {
	_strip.clear();
}

void Piano::fillStripColor(uint16_t from, uint16_t count, Color& color) {
	invertStripIndexIfRequired(from);

	_strip.fill(color.toUint32(), from, count);
}

void Piano::fillStripColor(Color& color) {
	fillStripColor(0, getStripLength(), color);
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

			for (const auto& callback : _onMidiRead) {
				callback(event);
			}

			if (_effect)
				_effect->handleEvent(*this, event);
		}
	}
}

void Piano::addOnMidiRead(const std::function<void(MidiEvent&)> &callback) {
	_onMidiRead.push_back(callback);
}

uint16_t Piano::noteToKey(uint8_t note) {
	return note - Piano::midiKeyMinimum;
}

uint16_t Piano::keyToStripIndex(uint16_t key) {
	return (uint16_t) ((float) key / (float) _keyCount * (float) getStripLength());
}

uint16_t Piano::noteToStripIndex(uint8_t note) {
	return keyToStripIndex(noteToKey(note));
}

Effect *Piano::getEffect() {
	return _effect;
}

void Piano::setEffect(Effect *newEffect) {
	_effect = newEffect;
}

uint8_t Piano::getKeyCount() const {
	return _keyCount;
}

void Piano::setKeyCount(uint8_t keyCount) {
	_keyCount = keyCount;
}

bool Piano::getIsStripInverted() const {
	return _isStripInverted;
}

void Piano::setIsStripInverted(bool value) {
	_isStripInverted = value;
}