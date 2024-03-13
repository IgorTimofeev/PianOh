#pragma once

#include "effect.h"
#include "grafica/color.h"
#include "devices/piano/piano.h"
#include "particles_effect.h"
#include "grafica/number.h"
#include "random.hpp"
#include "particles/flame_particle.h"

namespace devices { namespace piano {
	using Random = effolkronium::random_static;

	class FlameEffect : public ParticlesEffect {
		public:
			void handleEvent(Piano &piano, MidiEvent &event) override {
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

			void render(Piano &piano, const uint32_t &time) override {
				// Clearing
				for (int i = 0; i < piano.getStripLength(); i++) {
					piano.setStripColor(i, _backgroundColor);
				}

				// Rendering particles
				ParticlesEffect::render(piano, time);

				spawnSparks();
			}

			Color &getBackgroundColor() {
				return _backgroundColor;
			}

			void setBackgroundColor(Color &value) {
				_backgroundColor = value;
			}

		private:
			Color _backgroundColor = Color::black;
			std::map<uint8_t, FlameParticle *> _notesAndParticlesMap;

			void onNoteOn(Piano &piano, uint8_t note, uint8_t velocity) {
				auto floatVelocity = Number::clampFloat((float) velocity / 127.0f * 1.5f);

				auto particle = new FlameParticle();
				particle->position = piano.noteToStripIndex(note);
				particle->sizeLeft = 5;
				particle->sizeRight = 5;

				particle->brightness = floatVelocity;
				particle->brightnessMaximum = particle->brightness;
				particle->brightnessMinimum = particle->brightness * 0.4f;
				particle->brightnessLeft = 0.1;
				particle->brightnessRight = 0.1;

				particle->life = 0;
				particle->lifeVector = 0.2;

				_notesAndParticlesMap[note] = particle;

				addParticle(particle);
			}

			void onNoteOff(uint8_t note) {
				auto noteAndParticle = _notesAndParticlesMap.find(note);

				if (noteAndParticle == _notesAndParticlesMap.end())
					return;

				FlameParticle *particle = noteAndParticle->second;
				particle->lifeVector = -0.09;
				_notesAndParticlesMap.erase(note);
			}

			void spawnSparks() {
				const uint bigOffset = 6;
				const uint smallOffset = 4;

				bool isLeft;
				float isLeftFactor;
				FlameParticle *particle;

				for (auto keyAndParticle: _notesAndParticlesMap) {
					if (!Random::get<bool>(0.2))
						continue;

					isLeft = Random::get<bool>() == 1;
					isLeftFactor = isLeft ? -1.0f : 1.0f;

					particle = new FlameParticle();
					particle->position = keyAndParticle.second->position + isLeftFactor;
					particle->positionVector = isLeftFactor * Random::get(0.3f, 0.9f);
					particle->sizeLeft = isLeft ? bigOffset : smallOffset;
					particle->sizeRight = isLeft ? smallOffset : bigOffset;

					particle->brightness = keyAndParticle.second->brightnessMaximum * Random::get(0.1f, 0.3f);
					particle->brightnessMaximum = particle->brightness;
					particle->brightnessMinimum = particle->brightness * 0.4f;
					particle->brightnessLeft = isLeft ? 0.2 : 0.1;
					particle->brightnessRight = isLeft ? 0.1 : 0.2;

					particle->life = 1;
					particle->lifeVector = Random::get(-0.04f, -0.12f);

					addParticle(particle);
				}
			}
	};
}}