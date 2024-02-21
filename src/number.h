#pragma once

#include <cstdint>

class Number {
	public:
		static float clamp(float value, float minimum = 0, float maximum = 1);
		static int16_t clamp(int16_t value, int16_t minimum, int16_t maximum);
		static int32_t clamp(int32_t value, int32_t minimum, int32_t maximum);
};