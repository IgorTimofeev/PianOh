#pragma once

#include "effect.h"
#include "color.h"
#include "piano/piano.h"
#include "particles_effect.h"
#include "number.h"
#include "piano/particles/flame_particle.h"
#include "random.h"

using Random = effolkronium::random_static;

class WaterEffect : public ParticlesEffect {
	private:
		std::map<uint8_t, WaveParticle*> keysAndParticlesMap {};

	public:
		WaterEffect() = default;

		void spawnSplash(WaveParticle* mainParticle, bool isLeft) {
			float isLeftFactor = isLeft ? -1.0f : 1.0f;

			auto particle = new WaveParticle();
			particle->color = Color::water;
			particle->position = mainParticle->position + isLeftFactor * 2;
			particle->positionVector = isLeftFactor * 1.2f;
			particle->sizeLeft = 6;
			particle->sizeRight = 6;

			particle->brightness = mainParticle->brightness * 0.4f;
			particle->brightnessLeft = 0.1;
			particle->brightnessRight = 0.1;

			particle->life = 1;
			particle->lifeVector = -0.03;

			addParticle(particle);
		}

		void onNoteOn(Piano& piano, uint8_t note, uint8_t velocity) {
			auto floatVelocity = Number::clamp((float) velocity / 127.0f * 1.5f);

			auto key = Piano::noteToKey(note);

			auto particle = new WaveParticle();
			particle->color = Color::water;
			particle->position = piano.keyToStripIndex(key);
			particle->sizeLeft = 5;
			particle->sizeRight = 5;

			particle->brightness = floatVelocity;
			particle->brightnessLeft = 0.1;
			particle->brightnessRight = 0.1;

			particle->life = 0;
			particle->lifeVector = 0.3;

			keysAndParticlesMap[note] = particle;

			addParticle(particle);

			spawnSplash(particle, true);
			spawnSplash(particle, false);
		}

		void onNoteOff(uint8_t note) {
			WaveParticle* particle = keysAndParticlesMap[note];
			particle->lifeVector = -0.09;
			keysAndParticlesMap.erase(note);
		}

		void handleEvent(Piano& piano, MidiEvent& event) override {
			switch (event.type) {
				case midi::NoteOn:
					onNoteOn(piano, event.data1, event.data2);
					break;

				case midi::NoteOff:
					onNoteOff(event.data1);
					break;

				default:
					break;
			}
		}

		void render(Piano& piano) override {
			// Clearing
			piano.clearStrip();

			// Rendering particles
			ParticlesEffect::render(piano);
		}
};