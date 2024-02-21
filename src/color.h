#pragma once

#include <cstdint>

class Color {
	public:
		uint8_t r = 0;
		uint8_t g = 0;
		uint8_t b = 0;

		Color(uint8_t _r, uint8_t _g, uint8_t _b);

		Color(Color const &source);

		Color();

		explicit Color(uint32_t value);

		void multiply(float factor);

		void add(uint8_t _r, uint8_t _g, uint8_t _b);

		void add(const Color& color);

		uint32_t toUint32();
};