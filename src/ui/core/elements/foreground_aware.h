#pragma once

#include "element.h"
#include "ui/core/color.h"

namespace ui {
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
