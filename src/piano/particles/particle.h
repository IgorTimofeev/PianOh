#pragma once

#include "color.h"

class Piano;

class Particle {
	public:
		float position = 0;
		float life = 1;
		Color color;

		Particle() = default;

		virtual ~Particle() = default;

		virtual void render(Piano& piano) = 0;
};