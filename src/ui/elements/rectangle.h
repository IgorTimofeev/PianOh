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
				display.drawRectangle(getBounds(), getFillColor());
			}

			// -------------------------------- Getters & setters --------------------------------

		private:

	};
}
