#pragma once

#include "element.h"
#include "color.h"
#include "display.h"
#include "geometry/bounds.h"
#include "Fonts/Org_01.h"

namespace ui {
	class Rectangle : public Element {
		public:
			void render(Display& display) override {
				display.drawRectangle(getBounds(), getColor());
			}

			// -------------------------------- Getters & setters --------------------------------

			const Color& getColor() const {
				return _color;
			}

			void setColor(const Color& value) {
				_color = value;
			}

		private:
			Color _color = Color::white;
	};
}
