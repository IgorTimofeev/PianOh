#pragma once

#include "effect.h"
#include "grafica/color.h"
#include "devices/piano/piano.h"
#include "particles_effect.h"
#include "grafica/number.h"
#include "particles/flame_particle.h"

namespace devices {
	class RainbowEffect : public ParticlesEffect {
		public:
			void handleEvent(devices::Piano &piano, MidiEvent &event) override {
				switch (event.getType()) {
					case MidiType::NoteOn:
						onNoteOn(piano, event.getData1(), event.getData2());
						break;

					case MidiType::NoteOff:
						onNoteOff(event.getData1());
						break;

					default:
						break;
				}
			}

			void render(devices::Piano &piano, const uint32_t &time) override {
				piano.clearStrip();

				ParticlesEffect::render(piano, time);
			}

		private:
			std::map<uint8_t, WaveParticle *> notesAndParticlesMap;

			void onNoteOn(Piano &piano, uint8_t note, uint8_t velocity) {
				auto key = Piano::noteToKey(note);
				auto hue = (float) key / (float) piano.getKeyCount();

				auto particle = new WaveParticle();
				particle->color = Color(HsbColor(hue, 1, 1));
				particle->position = piano.keyToStripIndex(key);
				particle->sizeLeft = 2;
				particle->sizeRight = 2;
				particle->brightness = Number::clampFloat((float) velocity / 127.0f * 1.5f);
				particle->brightnessLeft = 0.2;
				particle->brightnessRight = 0.2;
				particle->life = 0;
				particle->lifeVector = 0.3;

				notesAndParticlesMap[note] = particle;

				addParticle(particle);
			}

			void onNoteOff(uint8_t note) {
				auto noteAndParticle = notesAndParticlesMap.find(note);

				if (noteAndParticle == notesAndParticlesMap.end())
					return;

				WaveParticle *particle = noteAndParticle->second;
				particle->lifeVector = -0.12;
				notesAndParticlesMap.erase(note);
			}
	};
}