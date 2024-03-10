#pragma once

enum MidiEventType: uint8_t {
	InvalidType           = 0x00,
	NoteOff               = 0x80,
	NoteOn                = 0x90,
	AfterTouchPoly        = 0xA0,
	ControlChange         = 0xB0,
	ProgramChange         = 0xC0,
	AfterTouchChannel     = 0xD0,
	PitchBend             = 0xE0,
	SystemExclusive       = 0xF0,
	SystemExclusiveStart  = SystemExclusive,
	TimeCodeQuarterFrame  = 0xF1,
	SongPosition          = 0xF2,
	SongSelect            = 0xF3,
	Undefined_F4          = 0xF4,
	Undefined_F5          = 0xF5,
	TuneRequest           = 0xF6,
	SystemExclusiveEnd    = 0xF7,
	Clock                 = 0xF8,
	Undefined_F9          = 0xF9,
	Tick                  = Undefined_F9,
	Start                 = 0xFA,
	Continue              = 0xFB,
	Stop                  = 0xFC,
	Undefined_FD          = 0xFD,
	ActiveSensing         = 0xFE,
	SystemReset           = 0xFF,
};

class MidiEvent {
	public:
		MidiEventType type;
		uint8_t channel;
		uint8_t data1;
		uint8_t data2;

		MidiEvent(MidiEventType type, uint8_t channel, uint8_t data1, uint8_t data2) :
			type(type),
			channel(channel),
			data1(data1),
			data2(data2)
		{

		}

		MidiEvent() : MidiEvent(MidiEventType::InvalidType, 0, 0, 0) {

		}

		MidiEvent& operator=(const MidiEvent& other) = default;

		static MidiEventType getEventTypeFromByte(const uint8_t& value) {
			return MidiEventType(value & 0b11110000);
		}

		static uint8_t getChannelFromByte(const uint8_t& value, const MidiEventType& eventType) {
			switch (eventType) {
				// Events with encoded channel value
				case NoteOff:
				case NoteOn:
				case ControlChange:
				case AfterTouchPoly:
				case AfterTouchChannel:
				case PitchBend:
				case ProgramChange:
					return (uint8_t) ((value & 0b1111) + 1);

				// No channel :(
				default:
					return 0;
			}
		}

		static uint8_t getLength(MidiEventType eventType) {
			switch (eventType) {
				// 2
				case ProgramChange:
				case AfterTouchChannel:
				case TimeCodeQuarterFrame:
				case SongSelect:
					return 2;

				// 3
				case NoteOn:
				case NoteOff:
				case ControlChange:
				case PitchBend:
				case AfterTouchPoly:
				case SongPosition:
					return 3;

				// 1
				default:
					return 1;
			}
		}

		static MidiEvent fromByteBuffer(uint8_t* buffer, int& index) {
			MidiEvent event;

			event.type = getEventTypeFromByte(buffer[index]);
			event.channel = getChannelFromByte(buffer[index], event.type);
			index++;

			auto eventLength = getLength(event.type);

			if (eventLength > 1) {
				event.data1 = buffer[index];
				index++;
			}

			if (eventLength > 2) {
				event.data2 = buffer[index];
				index++;
			}

			return event;
		}
};