#pragma once

class MidiEvent {
	public:
		const uint8_t type;
		const uint8_t channel;
		const uint8_t data1;
		const uint8_t data2;

		MidiEvent(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2) :
			type(type),
			channel(channel),
			data1(data1),
			data2(data2)
		{

		}
};