#include "piano/piano.h"
#include "piano/particles/particle.h"
#include "piano/effects/golden_effect.h"
#include <Midi.h>
#include "color.h"

// Override the default MIDI baudrate to
// a decoding program such as Hairless MIDI (set baudrate to 115200)
struct CustomBaudRateSettings : public MIDI_NAMESPACE::DefaultSerialSettings {
	static const long BaudRate = 115200;
};

MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings> serialMIDI(Serial);
MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>> MIDI((MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>&)serialMIDI);

Piano::Piano(uint8_t keysCount, uint16_t stripLEDCount, int16_t stripPin) : keysCount(keysCount) {
	strip = Adafruit_NeoPixel(stripLEDCount, stripPin, NEO_GRB + NEO_KHZ800);
}

Piano::~Piano() {
	delete effect;
}

uint16_t Piano::getStripLEDCount() {
	return strip.numPixels();
}

void Piano::invertStripIndexIfRequired(uint16_t& index) {
	if (isStripInverted)
		index = getStripLEDCount() - index - 1;
}

bool Piano::isStripIndexInRange(uint16_t index) {
	return index >= 0 && index < getStripLEDCount();
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

void Piano::begin() {
	MIDI.begin();
	strip.begin();
}

void Piano::updateStrip() {
	strip.show();
}

void Piano::renderStrip() {
	if (effect) {
		effect->render(*this);
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
	fillStrip(0, getStripLEDCount() - 1, color);
}

void Piano::readMidi() {
	while (MIDI.read()) {
		auto event = MidiEvent(MIDI.getType(), MIDI.getChannel(), MIDI.getData1(), MIDI.getData2());

		switch (event.type) {
			case midi::NoteOn:
				pressedKeysVelocities[noteToKey(event.data1)] = event.data2;
				break;

			case midi::NoteOff:
				pressedKeysVelocities.erase(noteToKey(event.data1));
				break;
		}

		for (const auto& callback : onMidiRead) {
			callback(event);
		}

		if (effect)
			effect->handleEvent(*this, event);
	}
}

void Piano::addOnMidiRead(const std::function<void(MidiEvent&)> &callback) {
	onMidiRead.push_back(callback);
}

uint16_t Piano::noteToKey(uint8_t note) {
	return note - Piano::midiKeyMinimum;
}

uint16_t Piano::keyToStripIndex(uint16_t key) {
	return (uint16_t) ((float) key / (float) keysCount * (float) getStripLEDCount());
}

uint16_t Piano::noteToStripIndex(uint8_t note) {
	return keyToStripIndex(noteToKey(note));
}

uint8_t Piano::getKeyVelocity(uint16_t index) {
	return pressedKeysVelocities.count(index) > 0 ? pressedKeysVelocities.at(index) : 0;
}

void Piano::setEffect(Effect *_effect) {
	delete effect;
	effect = _effect;
}
