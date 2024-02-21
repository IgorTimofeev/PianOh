#include "number.h"

float Number::clamp(float value, float minimum, float maximum) {
	if (value < minimum)
		value = minimum;
	else if (value > maximum)
		value = maximum;

	return value;
}

int16_t Number::clamp(int16_t value, int16_t minimum, int16_t maximum) {
	if (value < minimum)
		value = minimum;
	else if (value > maximum)
		value = maximum;

	return value;
}

int32_t Number::clamp(int32_t value, int32_t minimum, int32_t maximum) {
	if (value < minimum)
		value = minimum;
	else if (value > maximum)
		value = maximum;

	return value;
}
