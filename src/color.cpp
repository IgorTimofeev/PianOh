#include "color.h"
#include "number.h"

const Color Color::black = Color(0, 0, 0);
const Color Color::gold = Color(0xF2, 0xB3, 0x3A);
const Color Color::white = Color(0xFF, 0xFF, 0xFF);

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

Color::Color(const HsbColor &hsb) {
	auto hueSector = hsb.h * 6.0f;
	auto hueSectorIntegerPart = (uint8_t) hueSector;
	auto hueSectorFractionalPart = hueSector - (float) hueSectorIntegerPart;

	auto
		p = (uint8_t) (255.0f * hsb.b * (1 - hsb.s)),
		q = (uint8_t) (255.0f * hsb.b * (1 - hueSectorFractionalPart * hsb.s)),
		t = (uint8_t) (255.0f * hsb.b * (1 - (1 - hueSectorFractionalPart) * hsb.s)),
		v = (uint8_t) (255.0f * hsb.b);

	switch (hueSectorIntegerPart) {
		case 1:
			r = q;
			g = v;
			b = p;
			break;

		case 2:
			r = p;
			g = v;
			b = t;
			break;

		case 3:
			r = p;
			g = q;
			b = v;
			break;

		case 4:
			r = t;
			g = p;
			b = v;
			break;

		case 5:
			r = v;
			g = p;
			b = q;
			break;

		default:
			r = v;
			g = t;
			b = p;
			break;
	}
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
	r = (uint8_t) Number::clamp((int32_t) r + _r, (int32_t) 0, (int32_t) 255);
	g = (uint8_t) Number::clamp((int32_t) g + _g, (int32_t) 0, (int32_t) 255);
	b = (uint8_t) Number::clamp((int32_t) b + _b, (int32_t) 0, (int32_t) 255);
}

void Color::multiply(float factor) {
	r = (uint8_t) Number::clamp((float) r * factor, 0.0f, 255.0f);
	g = (uint8_t) Number::clamp((float) g * factor, 0.0f, 255.0f);
	b = (uint8_t) Number::clamp((float) b * factor, 0.0f, 255.0f);
}

uint32_t Color::toUint32() const {
	return r << 16 | g << 8 | b;
}