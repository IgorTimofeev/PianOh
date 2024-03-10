#pragma once

#include "piano/midi_event.h"

class Piano;

class Effect {
	public:
		Effect() = default;

		virtual ~Effect() = default;

		virtual void handleEvent(Piano& piano, MidiEvent& event) {

		}

		virtual void render(Piano& piano, const uint32_t& time) = 0;
};