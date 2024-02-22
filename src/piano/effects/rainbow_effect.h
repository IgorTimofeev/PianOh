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
		std::map<uint8_t, WaveParticle*> notesAndParticlesMap {};

	public:
		~RainbowEffect() override {
			notesAndParticlesMap.clear();
		}

		void onNoteOn(Piano& piano, uint8_t note, uint8_t velocity) {
			auto key = Piano::noteToKey(note);
			auto hue = (float) key / (float) piano.keysCount;

			auto particle = new WaveParticle();
			particle->color = Color(HsbColor(hue, 1, 1));
			particle->position = piano.keyToStripIndex(key);
			particle->sizeLeft = 2;
			particle->sizeRight = 2;
			particle->brightness = Number::clampFloat((float) velocity / 127.0f * 1.5f);
			particle->brightnessLeft = 0.2;
			particle->brightnessRight = 0.2;
			particle->life = 0.5;
			particle->lifeVector = 0.3;

			notesAndParticlesMap[note] = particle;

			addParticle(particle);
		}

		void onNoteOff(uint8_t note) {
			auto noteAndParticle = notesAndParticlesMap.find(note);

			if (noteAndParticle == notesAndParticlesMap.end())
				return;

			WaveParticle* particle = noteAndParticle->second;
			particle->lifeVector = -0.12;
			notesAndParticlesMap.erase(note);
		}

		void handleEvent(Piano& piano, MidiEvent& event) override {
			switch (event.type) {
				case MidiEventType::NoteOn:
					onNoteOn(piano, event.data1, event.data2);
					break;

				case MidiEventType::NoteOff:
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