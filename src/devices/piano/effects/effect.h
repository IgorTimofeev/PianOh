#pragma once

#include "devices/piano/midi_event.h"
#include "grafica/color.h"
#include <cstdint>

namespace ui {
	class Piano;
}

using namespace grafica;

namespace devices {
	class Piano;

	class Effect {
		public:
			Effect() = default;

			virtual ~Effect() = default;

			virtual void handleEvent(devices::Piano &piano, MidiEvent& event);

			virtual void render(devices::Piano &piano) = 0;

			virtual Color getSampleColor(devices::Piano &piano, const uint16_t &index);
	};
}