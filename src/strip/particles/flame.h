#pragma once

#include "particle.h"
#include "strip/strip.h"
#include "random.hpp"
#include "number.h"
#include "../color.h"

using Random = effolkronium::random_static;

class FlameParticle : public Particle {
	public:
		float positionVector = 0;
		float sizeLeft = 0;
		float sizeRight = 0;

		float brightness = 0;
		float brightnessMinimum = 0;
		float brightnessMaximum = 0;
		float brightnessVector = 0;

		float brightnessLeft = 0;
		float brightnessRight = 0;

		float lifeVector = 0;

		FlameParticle() {
			color.r = 0xF2;
			color.g = 0xBE;
			color.b = 0x3A;
		}

		void render(Strip& strip) override {
			int intPosition = (int) round(position);
			float sideFactor;

			for (int i = intPosition - (int) sizeLeft; i <= intPosition + (int) sizeRight; i++) {
				if (i < 0 || i >= strip.getLength())
					continue;

				if (i < intPosition) {
					sideFactor = (1 - (float) (intPosition - i) / sizeLeft) * brightnessLeft;
				}
				else if (i > intPosition) {
					sideFactor = (1 - (float) (i - intPosition) / sizeRight) * brightnessRight;
				}
				else {
					sideFactor = 1;
				}

				auto newColor = Color(color);

				newColor.multiply(life * brightness * sideFactor);
				newColor.add(strip.getColor(i));

				strip.setColor(i, newColor);
			}

			// Position
			position += positionVector;

			// Brightness
			brightness = Number::clampFloat(
				brightness + brightnessVector,
				brightnessMinimum,
				brightnessMaximum
			);

			brightnessVector = Random::get(-0.05f, 0.05f);

			// Life
			life = Number::clampFloat(life + lifeVector);
		}
};