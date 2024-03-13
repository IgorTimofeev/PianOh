#pragma once

#include "effect.h"
#include "grafica/color.h"
#include "devices/piano/piano.h"

namespace devices { namespace piano {
	class TestEffect : public Effect {
		public:
			uint8_t lastKey = 0;
			Color color;

			explicit TestEffect(const Color &color) : color(color) {

			}

			void handleEvent(Piano &piano, MidiEvent &event) override {
				switch (event.type) {
					case MidiType::NoteOn:
						lastKey = event.data1;
						break;

					case MidiType::NoteOff:
						lastKey = 0;
						break;

					default:
						break;
				}
			}

			void render(Piano &piano, const uint32_t &time) override {
				piano.clearStrip();
				piano.setStripColor(lastKey, color);
			}
	};
}}