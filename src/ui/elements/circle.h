#pragma once

#include "ui/elements/shape.h"
#include "ui/color.h"
#include "ui/display.h"
#include "cmath"

namespace ui {
	class Circle : public Shape {
		public:
			void render(Display& display) override {
				auto bounds = getBounds();

				display.drawCircle(
					Point(bounds.getX() + bounds.getWidth() / 2, bounds.getY() + bounds.getHeight() / 2),
					min(bounds.getWidth(), bounds.getHeight()) / 2,
					getFillColor()
				);
			}

			// -------------------------------- Getters & setters --------------------------------

		private:

	};
}
