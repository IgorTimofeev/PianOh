#pragma once

#include "element.h"
#include "ui/color.h"
#include "ui/display.h"
#include "ui/geometry/bounds.h"
#include "Fonts/Org_01.h"

namespace ui {
	class Rectangle : public Element {
		public:
			void render(Display& display) override {
				auto bounds = getBounds();
				display.drawRectangle(bounds, getColor());
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
