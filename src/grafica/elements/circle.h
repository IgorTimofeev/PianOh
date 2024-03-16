#pragma once

#include "shape.h"
#include "grafica/color.h"
#include "grafica/screen.h"
#include "cmath"

namespace grafica {
	class Circle : public Shape {
		public:
			void onRender(Screen& display) override {
				auto bounds = getBounds();

				display.renderCircle(
					Point(bounds.getX() + bounds.getWidth() / 2, bounds.getY() + bounds.getHeight() / 2),
					min(bounds.getWidth(), bounds.getHeight()) / 2,
					getFillColor()
				);
			}

			// -------------------------------- Getters & setters --------------------------------

		private:

	};
}
