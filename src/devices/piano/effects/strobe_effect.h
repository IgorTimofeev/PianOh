#pragma once

#include <unordered_set>
#include "effect.h"
#include "grafica/color.h"
#include "devices/piano/piano.h"
#include "particles_effect.h"
#include "grafica/number.h"

namespace devices {
	class StrobeEffect : public Effect {
		public:
			explicit StrobeEffect(const Color &color) : _color(color) {

			}

			void handleEvent(devices::Piano &piano, MidiEvent &event) override {
				switch (event.getType()) {
					case MidiType::NoteOn:
						onNoteOn(piano, event.getData1(), event.getData2());
						break;

					case MidiType::NoteOff:
						onNoteOff(piano, event.getData1());
						break;

					default:
						break;
				}
			}

			void render(devices::Piano &piano, const uint32_t &time) override {
				piano.clearStrip();

				if (time < _strobeDeadline || _pressedStripIndicesAndVelocities.empty())
					return;

				Color color;

				for (auto &stripIndexAndVelocity: _pressedStripIndicesAndVelocities) {
					color = _color;
					color.multiply(stripIndexAndVelocity.second);
					piano.setStripColor(stripIndexAndVelocity.first, color);
				}

				_strobeDeadline = time + _strobeInterval;
			}

			uint16_t getStrobeInterval() const {
				return _strobeInterval;
			}

			void setStrobeInterval(uint16_t value) {
				_strobeInterval = value;
			}

		private:
			std::map<uint8_t, float> _pressedStripIndicesAndVelocities;
			Color _color;
			uint32_t _strobeDeadline = 0;
			uint16_t _strobeInterval = 100;

			void onNoteOn(Piano &piano, uint8_t note, uint8_t velocity) {
				_pressedStripIndicesAndVelocities[piano.noteToStripIndex(note)] = (float) velocity / 127.f;
			}

			void onNoteOff(Piano &piano, uint8_t note) {
				_pressedStripIndicesAndVelocities.erase(piano.noteToStripIndex(note));
			}
	};
}