#pragma once

#include "filler.h"
#include "color.h"
#include "strip/strip.h"

class ColorFiller : public Filler {
	public:
		Color color;

		explicit ColorFiller(const Color& _color) {
			color = _color;
		}

		void render(Strip& strip) override {
//			for (int i = 0; i < strip.getLength(); i++) {
//				strip.setColor(i, color);
//			}

			strip.setColor(10, color);
		}
};