#pragma once

#include "ui/elements/element.h"
#include "ui/color.h"

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
