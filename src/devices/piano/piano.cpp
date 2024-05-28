#include "Arduino.h"
#include "devices/piano/effects/effect.h"
#include "piano.h"
#include "grafica/color.h"
#include "MIDI.h"

namespace devices {
	struct CustomMIDISettings : public MIDI_NAMESPACE::DefaultSettings {
		static const long BaudRate = 31250;
	};

	MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, CustomMIDISettings);

	Piano::Piano(uint16_t stripLEDCount, int16_t stripPin) {
		_strip = Adafruit_NeoPixel(stripLEDCount, stripPin, NEO_GRB + NEO_KHZ800);
	}

	uint16_t Piano::getStripLength() {
		return _strip.numPixels();
	}

	void Piano::invertStripIndexIfRequired(uint16_t& index) {
		if (getIsStripInverted())
			index = getStripLength() - index - 2;
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
			return Color::main1;

		invertStripIndexIfRequired(index);

		return Color(_strip.getPixelColor(index));
	}

	void Piano::setStripColor(uint16_t index, const Color& value) {
		if (!isStripIndexInRange(index))
			return;

		invertStripIndexIfRequired(index);

		_strip.setPixelColor(index, value.r, value.g, value.b);
	}

	void Piano::begin() {
		MIDI.begin(MIDI_CHANNEL_OMNI);
		_strip.begin();
	}

	void Piano::renderStrip() {
		if (_effect) {
			_effect->render(*this);
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

	void Piano::tick() {
		while (MIDI.read()) {
			MidiEvent event = MidiEvent(
				MIDI.getType(),
				MIDI.getChannel(),
				MIDI.getData1(),
				MIDI.getData2()
			);

			switch (event.getType()) {
				case MidiType::NoteOn:
					pressedKeysVelocities[Piano::noteToKey(event.getData1())] = event.getData2();
					break;

				case MidiType::NoteOff:
					pressedKeysVelocities.erase(Piano::noteToKey(event.getData1()));
					break;

				default:
					break;
			}

			_onMidiRead.call(event);

			if (_effect)
				_effect->handleEvent(*this, event);
		}
	}

	void Piano::addOnMidiRead(const std::function<void(MidiEvent&)> &callback) {
		_onMidiRead.add(callback);
	}

	uint16_t Piano::noteToKey(uint8_t note) {
		return note - Piano::midiKeyMinimum;
	}

	uint16_t Piano::keyToStripIndex(uint16_t key) {
		return (uint16_t) round(((float) key / (float) _keyCount * (float) getStripLength()));
	}

	uint16_t Piano::noteToStripIndex(uint8_t note) {
		return keyToStripIndex(noteToKey(note));
	}

	Effect *Piano::getEffect() {
		return _effect;
	}

	void Piano::setEffect(Effect *value) {
		_effect = value;
	}

	uint8_t Piano::getKeyCount() const {
		return _keyCount;
	}

	bool Piano::getIsStripInverted() const {
		return _isStripInverted;
	}

	void Piano::setIsStripInverted(bool value) {
		_isStripInverted = value;
	}

	uint8_t Piano::getKeyVelocity(uint16_t index) {
		auto kayAndVelocity = pressedKeysVelocities.find(index);

		return kayAndVelocity == pressedKeysVelocities.end() ? 0 : kayAndVelocity->second;
	}
}