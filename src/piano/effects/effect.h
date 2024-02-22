#pragma once

#include "midi_event.h"

class Piano;

class Effect {
	public:
		Effect() = default;

		virtual ~Effect() = default;

		virtual void handleEvent(Piano& piano, MidiEvent& event) {

		}

		virtual void render(Piano& piano) = 0;
};