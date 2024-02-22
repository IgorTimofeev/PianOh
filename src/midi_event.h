#pragma once

class MidiEvent {
	public:
		uint8_t type;
		uint8_t channel;
		uint8_t data1;
		uint8_t data2;

		MidiEvent(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2) :
			type(type),
			channel(channel),
			data1(data1),
			data2(data2)
		{

		}

		MidiEvent() : MidiEvent(0, 0, 0, 0) {

		}

		MidiEvent& operator=(const MidiEvent& other) = default;
};