
#include "strip/particles/flame_particle.h"
#include "strip/strip.h"
#include "color.h"
#include "random.h"
#include "number.h"

using Random = effolkronium::random_static;

FlameParticle::FlameParticle() {
	color.r = 0xF2;
	color.g = 0xBE;
	color.b = 0x3A;
}

void FlameParticle::render(Strip& strip) {
	int intPosition = (int) round(position);
	float sideFactor;

	for (int i = intPosition - (int) sizeLeft; i <= intPosition + (int) sizeRight; i++) {
		if (i < 0 || i >= strip.getLength())
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
		newColor.add(strip.getColor(i));

		strip.setColor(i, newColor);
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