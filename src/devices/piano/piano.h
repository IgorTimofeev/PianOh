#pragma once

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "devices/piano/effects/effect.h"
#include "grafica/color.h"
#include "grafica/action.h"
#include "map"
#include "MIDI.h"

using namespace grafica;

namespace devices { namespace piano {
	class Piano {
		public:
			Piano(uint16_t stripLEDCount, int16_t stripPin);

			static uint16_t noteToKey(uint8_t note);

			uint16_t keyToStripIndex(uint16_t key);

			uint16_t noteToStripIndex(uint8_t note);

			uint16_t getStripLength();

			bool isStripIndexInRange(uint16_t index);

			uint8_t getStripBrightness();

			void setStripBrightness(uint8_t value);

			Color getStripColor(uint16_t index);

			void setStripColor(uint16_t index, const Color& value);

			void begin();

			void renderStrip(const uint32_t& time);

			void clearStrip();

			void fillStripColor(uint16_t from, uint16_t to, Color& color);

			void fillStripColor(Color& color);

			void read();

			void addOnMidiRead(const std::function<void(MidiEvent&)> &callback);

			Effect* getEffect();
			void setEffect(Effect* value);

			uint8_t getKeyCount() const;

			bool getIsStripInverted() const;
			void setIsStripInverted(bool value);

			uint8_t getKeyVelocity(uint16_t index);

		private:
			static const uint8_t midiKeyMinimum = 21;
			const uint8_t _keyCount = 88;

			Adafruit_NeoPixel _strip;
			Effect* _effect = nullptr;
			bool _isStripInverted = true;

			Action<MidiEvent&> _onMidiRead {};

			std::map<uint16_t, uint8_t> pressedKeysVelocities;

			void invertStripIndexIfRequired(uint16_t& index);
	};
}}