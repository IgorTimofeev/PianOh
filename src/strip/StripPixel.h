#pragma once

#include "Number.h"

class ByteColor {
	public:
		uint8_t r = 0;
		uint8_t g = 0;
		uint8_t b = 0;

		ByteColor() = default;

		ByteColor(uint8_t r, uint8_t g, uint8_t b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}

		void multiply(float factor) {
			r = Number::clamp(r * factor);
			g = Number::clamp(g * factor);
			b = Number::clamp(b * factor);
		}
};