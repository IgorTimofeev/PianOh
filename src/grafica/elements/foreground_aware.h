#pragma once

#include "element.h"
#include "grafica/color.h"

namespace grafica {
	class ForegroundAware : virtual public Element {
		public:
			const Color &getForeground() const {
				return foreground;
			}

			void setForeground(const Color &value) {
				foreground = value;
			}

		private:
			Color foreground = Color::black;
	};
}
