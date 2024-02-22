#pragma once

#include "piano/piano.h"
#include "color.h"
#include "number.h"

class Particle {
	public:
		float position = 0;
		float positionVector = 0;
		float life = 1;
		float lifeVector = 0;
		Color color = Color::white;

		virtual ~Particle() = default;

		virtual void render(Piano& piano, const uint32_t& time) {
			// Life
			life = Number::clampFloat(life + lifeVector, 0.0f, 1.0f);

			// Position
			position += positionVector;
		}
};