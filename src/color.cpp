#include "color.h"
#include "number.h"

Color::Color(uint8_t _r, uint8_t _g, uint8_t _b) {
	r = _r;
	g = _g;
	b = _b;
}

Color::Color(const Color &source) {
	r = source.r;
	g = source.g;
	b = source.b;
}

Color::Color() {
	r = 0;
	g = 0;
	b = 0;
}

Color::Color(uint32_t value) {
	r = value >> 16 & 0xFF;
	g = value >> 8 & 0xFF;
	b = value & 0xFF;
}

void Color::add(const Color &color) {
	add(color.r, color.g, color.b);
}

void Color::add(uint8_t _r, uint8_t _g, uint8_t _b) {
	r = (uint8_t) Number::clamp((int16_t) r + _r, (int16_t) 0, (int16_t) 255);
	g = (uint8_t) Number::clamp((int16_t) g + _g, (int16_t) 0, (int16_t) 255);
	b = (uint8_t) Number::clamp((int16_t) b + _b, (int16_t) 0, (int16_t) 255);
}

void Color::multiply(float factor) {
	r = (uint8_t) Number::clamp((float) r * factor, 0.0f, 255.0f);
	g = (uint8_t) Number::clamp((float) g * factor, 0.0f, 255.0f);
	b = (uint8_t) Number::clamp((float) b * factor, 0.0f, 255.0f);
}

uint32_t Color::toUint32() {
	return r << 16 | g << 8 | b;
}