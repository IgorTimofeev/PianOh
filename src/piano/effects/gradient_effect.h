#pragma once

#include "effect.h"
#include "ui/color.h"
#include "piano/piano.h"
#include "particles_effect.h"
#include "number.h"
#include "ui/gradient.h"

class GradientEffect : public ParticlesEffect {
	public:
		GradientEffect() = default;

		~GradientEffect() override {
			delete _gradient;
		}

		explicit GradientEffect(LinearGradient* gradient) {
			setGradient(gradient);
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

		void render(Piano& piano, const uint32_t& time) override {
			piano.clearStrip();

			ParticlesEffect::render(piano, time);
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