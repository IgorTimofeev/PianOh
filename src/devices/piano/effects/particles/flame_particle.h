#pragma once

#include "wave_particle.h"
#include "devices/piano/piano.h"
#include "grafica/color.h"
#include "random.hpp"

namespace devices { namespace piano {
	using Random = effolkronium::random_static;

	class FlameParticle : public WaveParticle {
		private:
			uint32_t brightnessFactorUpdateDeadline = 0;

		public:
			float brightnessMinimum = 0;
			float brightnessMaximum = 0;
			float brightnessVector = 0;

			FlameParticle() {
				color = Color::gold;
			}

			void render(Piano &piano, const uint32_t &time) override {
				WaveParticle::render(piano, time);

				// Brightness
				brightness = Number::clampFloat(
					brightness + brightnessVector,
					brightnessMinimum,
					brightnessMaximum
				);

				if (time > brightnessFactorUpdateDeadline) {
					brightnessVector = Random::get(-0.05f, 0.05f);
					brightnessFactorUpdateDeadline = time + 100;
				}
			}
	};
}}