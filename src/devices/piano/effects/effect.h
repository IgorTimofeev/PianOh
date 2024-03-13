#pragma once

#include "devices/piano/midi_event.h"
#include <cstdint>

namespace devices { namespace piano {
	class Piano;

	class Effect {
		public:
			Effect() = default;

			virtual ~Effect() = default;

			virtual void handleEvent(Piano& piano, MidiEvent& event);

			virtual void render(Piano& piano, const uint32_t& time) = 0;
	};
}}