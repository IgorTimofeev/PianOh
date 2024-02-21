
#include "piano/particles/wave_particle.h"
#include "piano/piano.h"
#include "color.h"
#include "random.h"
#include "number.h"

using Random = effolkronium::random_static;

WaveParticle::WaveParticle() {
	color = Color::gold;
}

void WaveParticle::render(Piano& piano) {
	int intPosition = (int) round(position);
	float sideFactor;

	for (int i = intPosition - sizeLeft; i <= intPosition + sizeRight; i++) {
		if (i < 0 || i >= piano.getStripLEDCount())
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

	// Life
	life = Number::clamp(life + lifeVector);
}