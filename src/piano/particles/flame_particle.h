#pragma once

#include "wave_particle.h"
#include "piano/piano.h"
#include "color.h"

class FlameParticle : public WaveParticle {
	public:
		float positionVector = 0;
		float brightnessMinimum = 0;
		float brightnessMaximum = 0;
		float brightnessVector = 0;

		FlameParticle();

		void render(Piano& piano) override;
};