#pragma once

#include "particle.h"
#include "piano/piano.h"
#include "color.h"

class WaveParticle : public Particle {
	public:
		uint16_t sizeLeft = 0;
		uint16_t sizeRight = 0;
		float brightness = 0;
		float brightnessLeft = 0;
		float brightnessRight = 0;

		WaveParticle();

		void render(Piano& piano) override;
};