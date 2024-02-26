#pragma once

#include "element.h"
#include "color.h"
#include "screen/display.h"
#include "screen/ui/geometry/bounds.h"
#include "fonts/Org_01.h"

namespace ui {
	class Rectangle : public Element {
		public:
			void render(Display& display) override {
				debugPrintBounds("[rect]");

				display.drawRectangle(Bounds(getCalculatedPosition(), getCalculatedSize()), getColor());
			}

			// -------------------------------- Getters & setters --------------------------------

			const Color &getColor() const {
				return _color;
			}

			void setColor(const Color& value) {
				_color = value;
			}

		private:
			Color _color = Color::white;
	};
}
