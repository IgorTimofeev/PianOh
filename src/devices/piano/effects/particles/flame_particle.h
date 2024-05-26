#pragma once

#include "wave_particle.h"
#include "devices/piano/piano.h"
#include "grafica/color.h"
#include "random.hpp"

namespace devices {
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

			void render(Piano &piano) override {
				WaveParticle::render(piano);

				// Brightness
				brightness = Number::clampFloat(
					brightness + brightnessVector,
					brightnessMinimum,
					brightnessMaximum
				);

				if (micros() > brightnessFactorUpdateDeadline) {
					brightnessVector = Random::get(-0.05f, 0.05f);
					brightnessFactorUpdateDeadline = micros() + 100;
				}
			}
	};
}