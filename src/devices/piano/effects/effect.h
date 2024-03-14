#pragma once

#include "devices/piano/midi_event.h"
#include <cstdint>

namespace ui {
	class Piano;
}

namespace devices {
	class Piano;

	class Effect {
		public:
			Effect() = default;

			virtual ~Effect() = default;

			virtual void handleEvent(devices::Piano &piano, MidiEvent& event);

			virtual void render(devices::Piano &piano, const uint32_t& time) = 0;

			virtual void example(ui::Piano& piano);
	};
}