
#include "piano/particles/flame_particle.h"
#include "piano/piano.h"
#include "color.h"
#include "random.h"
#include "number.h"

using Random = effolkronium::random_static;

FlameParticle::FlameParticle() {
	color = Color::gold;
}

void FlameParticle::render(Piano& piano) {
	WaveParticle::render(piano);

	// Brightness
	brightness = Number::clamp(
		brightness + brightnessVector,
		brightnessMinimum,
		brightnessMaximum
	);

	brightnessVector = Random::get(-0.05f, 0.05f);
}