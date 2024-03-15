#pragma once

#include "effect.h"
#include "particles/particle.h"
#include "devices/piano/piano.h"
#include "grafica/color.h"

namespace devices {
	class ParticlesEffect : public Effect {
		protected:
			std::vector<Particle*> particles;

		public:
			~ParticlesEffect() override {
				for (auto & particle : particles)
					delete particle;
			}

			void addParticle(Particle* particle) {
				particles.push_back(particle);
			}

			void removeParticleAt(uint16_t index) {
				auto particle = particles[index];
				particles.erase(particles.begin() + index);
				delete particle;
			}

			void render(devices::Piano &piano) override {
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
}