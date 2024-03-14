#include "effect.h"
#include "ui/elements/piano/piano.h"
#include "devices/piano/piano.h"

namespace devices {
	void Effect::handleEvent(devices::Piano &piano, MidiEvent &event) {

	}

	Color Effect::getSampleColor(devices::Piano &piano, const uint16_t &index) {
		return Color::gray;
	}
}