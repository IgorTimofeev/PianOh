#pragma once

#include "particle.h"
#include "piano/piano.h"
#include "color.h"

class FlameParticle : public Particle {
	public:
		float positionVector = 0;
		uint8_t sizeLeft = 0;
		uint8_t sizeRight = 0;

		float brightness = 0;
		float brightnessMinimum = 0;
		float brightnessMaximum = 0;
		float brightnessVector = 0;

		float brightnessLeft = 0;
		float brightnessRight = 0;

		float lifeVector = 0;

		FlameParticle();

		void render(Piano& piano) override;
};