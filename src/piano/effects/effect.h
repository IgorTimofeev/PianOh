#pragma once

#include <Midi.h>
#include "midi_event.h"

class Piano;

class Effect {
	public:
		Effect() = default;

		virtual ~Effect() = default;

		virtual void handleEvent(Piano& piano, const MidiEvent& event) {

		}

		virtual void render(Piano& piano) = 0;
};