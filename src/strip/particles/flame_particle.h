#pragma once

#include "particle.h"
#include "strip/strip.h"
#include "color.h"

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

		FlameParticle();

		void render(Strip& strip) override;
};