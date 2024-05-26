#include "color.h"
#include "number.h"

namespace grafica {
	const Color Color::black = Color(0x00, 0x00, 0x00);
	const Color Color::white = Color(0xFF, 0xFF, 0xFF);
	const Color Color::gold = Color(0xF2, 0xB3, 0x3A);
	const Color Color::water = Color(0x00, 0x73, 0xB5);

	const Color Color::main1 = Color(0x00, 0x00, 0x00);
	const Color Color::main2 = Color(0x08, 0x08, 0x08);
	const Color Color::main3 = Color(0x10, 0x10, 0x10);
	const Color Color::main4 = Color(0x18, 0x18, 0x18);
	const Color Color::main5 = Color(0x21, 0x20, 0x21);
	const Color Color::main6 = Color(0x29, 0x28, 0x29);
	const Color Color::main7 = Color(0x31, 0x30, 0x31);
	const Color Color::main8 = Color(0x39, 0x38, 0x39);
	const Color Color::main9 = Color(0x42, 0x40, 0x42);

	const Color Color::alt1 = Color(0xFF, 0xFF, 0xFF);
	const Color Color::alt2 = Color(0xEE, 0xEE, 0xEE);
	const Color Color::alt3 = Color(0xDD, 0xDD, 0xDD);
	const Color Color::alt4= Color(0xCC, 0xCC, 0xCC);
	const Color Color::alt5 = Color(0xBB, 0xBB, 0xBB);
	const Color Color::alt6 = Color(0xAA, 0xAA, 0xAA);
	const Color Color::alt7 = Color(0x99, 0x99, 0x99);
	const Color Color::alt8 = Color(0x88, 0x88, 0x88);
	const Color Color::alt9 = Color(0x77, 0x77, 0x77);

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
		r = (uint8_t) Number::clampInt32(r + _r, 0, 255);
		g = (uint8_t) Number::clampInt32(g + _g, 0, 255);
		b = (uint8_t) Number::clampInt32(b + _b, 0, 255);
	}

	void Color::multiply(float factor) {
		r = (uint8_t) Number::clampFloat((float) r * factor, 0.0f, 255.0f);
		g = (uint8_t) Number::clampFloat((float) g * factor, 0.0f, 255.0f);
		b = (uint8_t) Number::clampFloat((float) b * factor, 0.0f, 255.0f);
	}

	uint32_t Color::toUint32() const {
		return r << 16 | g << 8 | b;
	}

	uint8_t Color::interpolateChannel(uint8_t first, uint8_t second, float position) {
		return (uint8_t) ((float) first + (float) (second - first) * position);
	}

	void Color::interpolateTo(Color &second, float position) {
		r = interpolateChannel(r, second.r, position);
		g = interpolateChannel(g, second.g, position);
		b = interpolateChannel(b, second.b, position);
	}
}