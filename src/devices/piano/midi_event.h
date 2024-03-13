#pragma once

#include "MIDI.h"
#include <cstdint>

using namespace midi;

class MidiEvent {
	public:
		MidiType type;
		uint8_t channel;
		uint8_t data1;
		uint8_t data2;

		MidiEvent(MidiType type, uint8_t channel, uint8_t data1, uint8_t data2) :
			type(type),
			channel(channel),
			data1(data1),
			data2(data2)
		{

		}

		MidiEvent() : MidiEvent(MidiType::InvalidType, 0, 0, 0) {

		}

		MidiEvent& operator=(const MidiEvent& other) = default;
};