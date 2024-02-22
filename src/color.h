#pragma once

#include <cstdint>
#include "number.h"

class HsbColor {
	public:
		float h = 0;
		float s = 0;
		float b = 0;

	HsbColor(float h, float s, float b) : h(h), s(s), b(b) {

	}
};

class Color {
	public:
		static const Color black;
		static const Color gold;
		static const Color white;
		static const Color water;

		uint8_t r = 0;
		uint8_t g = 0;
		uint8_t b = 0;

		Color(uint8_t _r, uint8_t _g, uint8_t _b);

		Color(Color const &source);

		explicit Color(const HsbColor &hsb);

		Color();

		explicit Color(uint32_t value);

		void multiply(float factor);

		void add(uint8_t _r, uint8_t _g, uint8_t _b);

		void add(const Color& color);

		uint32_t toUint32() const;

		static uint8_t interpolateChannel(uint8_t first, uint8_t second, float position) {
			return (uint8_t) ((float) first + (float) (second - first) * position);
		}

		void interpolateTo(Color& second, float position) {
			r = interpolateChannel(r, second.r, position);
			g = interpolateChannel(g, second.g, position);
			b = interpolateChannel(b, second.b, position);
		}
};