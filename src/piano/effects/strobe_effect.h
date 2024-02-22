#pragma once

#include <unordered_set>
#include "effect.h"
#include "color.h"
#include "piano/piano.h"
#include "particles_effect.h"
#include "number.h"

class StrobeEffect : public Effect {
	public:
		explicit StrobeEffect(const Color& color) : _color(color) {

		}

		void handleEvent(Piano& piano, MidiEvent& event) override {
			switch (event.type) {
				case MidiEventType::NoteOn:
					onNoteOn(piano, event.data1, event.data2);
					break;

				case MidiEventType::NoteOff:
					onNoteOff(piano, event.data1);
					break;

				default:
					break;
			}
		}

		void render(Piano& piano, const uint32_t& time) override {
			piano.clearStrip();

			if (time < _strobeDeadline || _pressedStripIndices.empty())
				return;

			for (auto& index : _pressedStripIndices)
				piano.setStripColor(index, _color);

			_strobeDeadline = time + 100;
		}

	private:
		std::unordered_set<uint8_t> _pressedStripIndices;
		Color _color;
		uint32_t _strobeDeadline = 0;

		void onNoteOn(Piano& piano, uint8_t note, uint8_t velocity) {
			_pressedStripIndices.insert(piano.noteToStripIndex(note));
		}

		void onNoteOff(Piano& piano, uint8_t note) {
			_pressedStripIndices.erase(piano.noteToStripIndex(note));
		}
};