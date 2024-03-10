#pragma once

#include "Adafruit_NeoPixel.h"
#include <vector>
#include <map>
#include "ui/core/color.h"
#include "piano/effects/effect.h"
#include "midi_event.h"
#include "ui/core/action.h"

class Particle;

class Piano {
	public:
		static const uint8_t midiKeyMinimum = 21;

		Piano(uint8_t keyCount, uint16_t stripLEDCount, int16_t stripPin);

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

		void renderStrip(const uint32_t& time);

		void clearStrip();

		void fillStripColor(uint16_t from, uint16_t to, Color& color);

		void fillStripColor(Color& color);

		void readMidiEvents();

		void addOnMidiRead(const std::function<void(MidiEvent&)> &callback);

		Effect* getEffect();
		void setEffect(Effect* newEffect);

		uint8_t getKeyCount() const;
		void setKeyCount(uint8_t keyCount);

		bool getIsStripInverted() const;
		void setIsStripInverted(bool value);

	private:
		Adafruit_NeoPixel _strip;
		Effect* _effect = nullptr;
		uint8_t _keyCount;
		bool _isStripInverted = true;

		Action<MidiEvent&> _onMidiRead {};

		void invertStripIndexIfRequired(uint16_t& index);
};