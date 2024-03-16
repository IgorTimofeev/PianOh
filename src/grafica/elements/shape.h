#pragma once

#include "element.h"
#include "grafica/color.h"
#include "grafica/screen.h"

namespace grafica {
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
