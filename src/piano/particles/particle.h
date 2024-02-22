#pragma once

#include "color.h"
#include "number.h"

class Piano;

class Particle {
	public:
		float position = 0;
		float positionVector = 0;
		float life = 1;
		float lifeVector = 0;
		Color color = Color::white;

		virtual ~Particle() = default;

		virtual void render(Piano& piano) {
			// Life
			life = Number::clamp(life + lifeVector, 0.0f, 1.0f);

			// Position
			position += positionVector;
		}
};