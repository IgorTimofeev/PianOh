#pragma once

#include "effect.h"
#include "grafica/color.h"
#include "devices/piano/piano.h"

namespace devices {
	class TestEffect : public Effect {
		public:
			uint8_t lastKey = 0;
			Color color;

			explicit TestEffect(const Color &color) : color(color) {

			}

			void handleEvent(devices::Piano &piano, MidiEvent &event) override {
				switch (event.getType()) {
					case MidiType::NoteOn:
						lastKey = event.getData1();
						break;

					case MidiType::NoteOff:
						lastKey = 0;
						break;

					default:
						break;
				}
			}

			void render(devices::Piano &piano, const uint32_t &time) override {
				piano.clearStrip();
				piano.setStripColor(lastKey, color);
			}
	};
}