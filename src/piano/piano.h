#pragma once

#include "Adafruit_NeoPixel.h"
#include <vector>
#include <map>
#include "color.h"
#include "piano/effects/effect.h"
#include "midi_event.h"

class Particle;

class Piano {
	private:
		Adafruit_NeoPixel strip;
		Effect* effect = nullptr;

		void invertStripIndexIfRequired(uint16_t& index);

	public:
		static const uint8_t midiKeyMinimum = 21;

		const uint8_t keysCount;

		bool isStripInverted = true;

		std::vector<std::function<void(MidiEvent&)>> onMidiRead;

		Piano(uint8_t keysCount, uint16_t stripLEDCount, int16_t stripPin);

		~Piano();

		static uint16_t noteToKey(uint8_t note);
		uint16_t keyToStripIndex(uint16_t key);
		uint16_t noteToStripIndex(uint8_t note);

		uint16_t getStripLength();

		bool isStripIndexInRange(uint16_t index);

		uint8_t getStripBrightness();

		void setStripBrightness(uint8_t value);

		Color getStripColor(uint16_t index);

		void setStripColor(uint16_t index, const Color& value);

		void begin(uint32_t stripBaudRate = 31250);

		void updateStrip();

		void renderStrip(const uint32_t& time);

		void clearStrip();

		void fillStrip(uint16_t from, uint16_t to, Color& color);

		void fillStrip(Color& color);

		void readMidiEvents();

		void addOnMidiRead(const std::function<void(MidiEvent&)> &callback);

		void setEffect(Effect* newEffect) {
			delete effect;
			effect = newEffect;
		}
};