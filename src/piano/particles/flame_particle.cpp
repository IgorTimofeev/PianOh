
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
	int intPosition = (int) round(position);
	float sideFactor;

	for (int i = intPosition - (int) sizeLeft; i <= intPosition + (int) sizeRight; i++) {
		if (i < 0 || i >= piano.getStripLEDCount())
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
		newColor.add(piano.getStripColor(i));

		piano.setStripColor(i, newColor);
	}

	// Position
	position += positionVector;

	// Brightness
	brightness = Number::clamp(
		brightness + brightnessVector,
		brightnessMinimum,
		brightnessMaximum
	);

	brightnessVector = Random::get(-0.05f, 0.05f);

	// Life
	life = Number::clamp(life + lifeVector);
}