#pragma once

#include "effect.h"
#include "grafica/color.h"
#include "devices/piano/piano.h"
#include "particles_effect.h"
#include "grafica/number.h"
#include "particles/flame_particle.h"

namespace devices {
	using Random = effolkronium::random_static;

	class WaterEffect : public ParticlesEffect {
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

			void render(devices::Piano &piano) override {
				// Clearing
				piano.clearStrip();

				// Rendering particles
				ParticlesEffect::render(piano);
			}

		private:
			std::map<uint8_t, WaveParticle *> _notesAndParticlesMap{};

			void spawnSplash(WaveParticle *mainParticle, bool isLeft, uint16_t offset, float positionVector,
							 float brightness) {
				float isLeftFactor = isLeft ? -1.0f : 1.0f;

				auto particle = new WaveParticle();
				particle->color = Color::water;
				particle->position = mainParticle->position + isLeftFactor * (float) offset;
				particle->positionVector = isLeftFactor * positionVector;
				particle->sizeLeft = 5;
				particle->sizeRight = 5;

				particle->brightness = mainParticle->brightness * brightness;
				particle->brightnessLeft = 0.4;
				particle->brightnessRight = 0.4;

				particle->life = 1;
				particle->lifeVector = -0.03;

				addParticle(particle);
			}

			void spawnSplashes(WaveParticle *particle, uint16_t offset, float positionVector, float brightness) {
				spawnSplash(particle, true, offset, positionVector, brightness);
				spawnSplash(particle, false, offset, positionVector, brightness);
			}

			void onNoteOn(Piano &piano, uint8_t note, uint8_t velocity) {
				auto floatVelocity = Number::clampFloat((float) velocity / 127.0f * 1.5f);

				auto key = Piano::noteToKey(note);

				auto particle = new WaveParticle();
				particle->color = Color::water;
				particle->position = piano.keyToStripIndex(key);
				particle->sizeLeft = 5;
				particle->sizeRight = 5;

				particle->brightness = floatVelocity;
				particle->brightnessLeft = 0.4;
				particle->brightnessRight = 0.4;

				particle->life = 0;
				particle->lifeVector = 0.3;

				_notesAndParticlesMap[note] = particle;

				addParticle(particle);

				spawnSplashes(particle, 1, 1.0f, 0.8f * floatVelocity);
				spawnSplashes(particle, 9, 1.3f, 0.4f * floatVelocity);
				spawnSplashes(particle, 18, 1.6f, 0.1f * floatVelocity);
			}

			void onNoteOff(uint8_t note) {
				auto noteAndParticle = _notesAndParticlesMap.find(note);

				if (noteAndParticle == _notesAndParticlesMap.end())
					return;

				WaveParticle *particle = noteAndParticle->second;
				particle->lifeVector = -0.09;
				_notesAndParticlesMap.erase(note);
			}
	};
}