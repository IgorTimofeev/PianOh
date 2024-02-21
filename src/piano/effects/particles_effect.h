#pragma once

#include "piano/effects/effect.h"
#include "piano/particles/particle.h"
#include "piano/piano.h"
#include "color.h"

class ParticlesEffect : public Effect {
	protected:
		std::vector<Particle*> particles;

	public:
		explicit ParticlesEffect() = default;

		~ParticlesEffect() override {
			for (auto particle : particles) {
				delete particle;
			}
		}

		void addParticle(Particle* particle) {
			particles.push_back(particle);
		}

		void removeParticleAt(uint16_t index) {
			auto particle = particles[index];
			particles.erase(particles.begin() + index);
			delete particle;
		}

		void render(Piano& piano) override {
			Particle* particle;

			for (int i = 0; i < particles.size(); i++) {
				particle = particles[i];

				particle->render(piano);

				if (particle->life <= 0) {
					removeParticleAt(i);
					i--;
				}
			}
		}
};