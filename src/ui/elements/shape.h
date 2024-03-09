#pragma once

#include "element.h"
#include "ui/color.h"
#include "ui/display.h"

namespace ui {
	class Shape : public Element {
		public:
			const Color& getFillColor() const {
				return _fillColor;
			}

			void setFillColor(const Color& value) {
				_fillColor = value;
			}

		private:
			Color _fillColor = Color::black;
	};
}
