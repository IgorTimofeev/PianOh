#pragma once

#include "number.h"

class Color {
	public:
		uint8_t r = 0;
		uint8_t g = 0;
		uint8_t b = 0;

		Color(uint8_t _r, uint8_t _g, uint8_t _b) {
			r = _r;
			g = _g;
			b = _b;
		}

		Color(Color const &source) {
			r = source.r;
			g = source.g;
			b = source.b;
		}

		Color() {
			r = 0;
			g = 0;
			b = 0;
		}

		explicit Color(uint32_t value) {
			r = value >> 16;
			g = value >> 8 & 0xFF;
			b = value & 0xFF;
		}

		void multiply(float factor) {
			r = (uint8_t) Number::clampFloat((float) r * factor, 0, 255);
			g = (uint8_t) Number::clampFloat((float) g * factor, 0, 255);
			b = (uint8_t) Number::clampFloat((float) b * factor, 0, 255);
		}

		void add(uint8_t _r, uint8_t _g, uint8_t _b) {
			r = (uint8_t) Number::clampInt(r + _r, 0, 255);
			g = (uint8_t) Number::clampInt(g + _g, 0, 255);
			b = (uint8_t) Number::clampInt(b + _b, 0, 255);
		}

		void add(const Color& color) {
			add(color.r, color.g, color.b);
		}
};