#pragma once

class Number {
	public:
		static float clamp(float value, float minimum = 0, float maximum = 1) {
			if (value < minimum)
				value = minimum;
			else if (value > maximum)
				value = maximum;

			return value;
		}
};