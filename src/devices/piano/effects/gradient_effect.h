#pragma once

#include "effect.h"
#include "grafica/color.h"
#include "devices/piano/piano.h"
#include "particles_effect.h"
#include "grafica/number.h"
#include "grafica/gradient.h"
#include "ui/elements/piano/piano.h"
#include "particles/wave_particle.h"

namespace devices {
	class GradientEffect : public ParticlesEffect {
		public:
			~GradientEffect() override {
				delete _gradient;
			}

			void handleEvent(devices::Piano &piano, MidiEvent& event) override {
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

			void render(devices::Piano &piano, const uint32_t& time) override {
				piano.clearStrip();

				ParticlesEffect::render(piano, time);
			}

			Color getSampleColor(devices::Piano &piano, const uint16_t &index) override {
				if (!_gradient)
					return Effect::getSampleColor(piano, index);

				return _gradient->getColor((float) index / (float) piano.getStripLength());
			}

			LinearGradient* getGradient() {
				return _gradient;
			}

			void setGradient(LinearGradient* gradient) {
				_gradient = gradient;
			}

		private:
			LinearGradient* _gradient = nullptr;
			std::map<uint8_t, WaveParticle*> _notesAndParticlesMap;

			void onNoteOn(Piano& piano, uint8_t note, uint8_t velocity) {
				if (!_gradient)
					return;

				auto key = Piano::noteToKey(note);
				auto position = (float) key / (float) piano.getKeyCount();

				auto particle = new WaveParticle();
				particle->color = _gradient->getColor(position);
				particle->position = piano.keyToStripIndex(key);
				particle->sizeLeft = 3;
				particle->sizeRight = 3;
				particle->brightness = Number::clampFloat((float) velocity / 127.0f * 1.5f);
				particle->brightnessLeft = 0.5;
				particle->brightnessRight = 0.5;
				particle->life = 0;
				particle->lifeVector = 0.3;

				_notesAndParticlesMap[note] = particle;

				addParticle(particle);
			}

			void onNoteOff(uint8_t note) {
				auto noteAndParticle = _notesAndParticlesMap.find(note);

				if (noteAndParticle == _notesAndParticlesMap.end())
					return;

				WaveParticle* particle = noteAndParticle->second;
				particle->lifeVector = -0.12;
				_notesAndParticlesMap.erase(note);
			}
	};
}