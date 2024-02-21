#pragma once

#include "effect.h"
#include "color.h"
#include "piano/piano.h"
#include "particles_effect.h"
#include "number.h"
#include "piano/particles/flame_particle.h"
#include "random.h"

class RainbowEffect : public ParticlesEffect {
	private:
		std::map<int, FlameParticle*> keysAndParticlesMap;

	public:
		explicit RainbowEffect() = default;

		void onNoteOn(Piano& piano, uint8_t note, uint8_t velocity) {
			auto key = Piano::noteToKeyIndex(note);

			auto particle = new FlameParticle();
			particle->position = piano.keyToStripIndex(key);
			particle->sizeLeft = 2;
			particle->sizeRight = 2;
			particle->brightness = Number::clamp((float) velocity / 127.0f * 1.5f);
			particle->brightnessMaximum = particle->brightness;
			particle->brightnessMinimum = particle->brightness * 0.4f;
			particle->brightnessLeft = 0.2;
			particle->brightnessRight = 0.2;
			particle->life = 0;
			particle->lifeVector = 0.2;

			keysAndParticlesMap[key] = particle;

			addParticle(particle);
		}

		void onNoteOff(uint8_t note) {
			auto index = Piano::noteToKeyIndex(note);

			FlameParticle* particle = keysAndParticlesMap[index];
			particle->lifeVector = -0.09;
			keysAndParticlesMap.erase(index);
		}

		void handleEvent(Piano& piano, const MidiEvent& event) override {
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
			piano.clearStrip();

			ParticlesEffect::render(piano);
		}
};