#pragma once

#include "MIDI.h"
#include <cstdint>

using namespace midi;

namespace devices {
	class MidiEvent {
		public:
			MidiEvent(MidiType type, uint8_t channel, uint8_t data1, uint8_t data2) :
				_type(type),
				_channel(channel),
				_data1(data1),
				_data2(data2)
			{

			}

			MidiEvent() : MidiEvent(MidiType::InvalidType, 0, 0, 0) {

			}

			MidiEvent& operator=(const MidiEvent& other) = default;

			MidiType getType() const {
				return _type;
			}

			void setType(MidiType type) {
				_type = type;
			}

			uint8_t getChannel() const {
				return _channel;
			}

			void setChannel(uint8_t channel) {
				_channel = channel;
			}

			uint8_t getData1() const {
				return _data1;
			}

			void setData1(uint8_t data1) {
				_data1 = data1;
			}

			uint8_t getData2() const {
				return _data2;
			}

			void setData2(uint8_t data2) {
				_data2 = data2;
			}

		private:
			MidiType _type;
			uint8_t _channel;
			uint8_t _data1;
			uint8_t _data2;
	};
}