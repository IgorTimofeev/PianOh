#pragma once

#include "ui/elements/shape.h"
#include "ui/color.h"
#include "ui/display.h"

namespace ui {
	class Rectangle : public Shape {
		public:
			Rectangle() = default;

			explicit Rectangle(const Color& color) {
				setFillColor(color);
			}

			void render(Display& display) override {
				display.drawRectangle(getBounds(), getCornerRadius(), getFillColor());
			}

			// -------------------------------- Getters & setters --------------------------------

			uint8_t getCornerRadius() const {
				return _cornerRadius;
			}

			void setCornerRadius(uint8_t value) {
				_cornerRadius = value;
			}

		private:
			uint8_t _cornerRadius = 0;
	};
}
