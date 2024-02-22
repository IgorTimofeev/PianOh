#pragma once

#include "effect.h"
#include "color.h"
#include "piano/piano.h"
#include "particles_effect.h"

class TestEffect : public Effect {
public:
	uint8_t lastKey = 0;

	Color color;

	explicit TestEffect(const Color& color) : color(color) {

	}

	void handleEvent(Piano& piano, MidiEvent& event) override {
		switch (event.type) {
			case MidiEventType::NoteOn:
				lastKey = event.data1;
				break;

			case MidiEventType::NoteOff:
				lastKey = 0;
				break;

			default:
				break;
		}
	}

	void render(Piano& piano) override {
		piano.clearStrip();
		piano.setStripColor(lastKey, color);
	}
};