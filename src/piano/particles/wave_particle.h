#pragma once

#include "particle.h"
#include "piano/piano.h"
#include "grafica/color.h"

class WaveParticle : public Particle {
	public:
		uint16_t sizeLeft = 0;
		uint16_t sizeRight = 0;
		float brightness = 0;
		float brightnessLeft = 0;
		float brightnessRight = 0;

		WaveParticle() {
			color = Color::water;
		}

		void render(Piano& piano, const uint32_t& time) override {
			int intPosition = (int) round(position);
			float sideFactor;

			for (int i = intPosition - sizeLeft; i <= intPosition + sizeRight; i++) {
				if (i < 0 || i >= piano.getStripLength())
					continue;

				if (i < intPosition) {
					sideFactor = (1 - (float) (intPosition - i) / (float) sizeLeft) * brightnessLeft;
				}
				else if (i > intPosition) {
					sideFactor = (1 - (float) (i - intPosition) / (float) sizeRight) * brightnessRight;
				}
				else {
					sideFactor = 1;
				}

				auto newColor = Color(color);

				newColor.multiply(life * brightness * sideFactor);
				newColor.add(piano.getStripColor(i));

				piano.setStripColor(i, newColor);
			}

			Particle::render(piano, time);
		}
};