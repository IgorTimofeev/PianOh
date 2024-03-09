#pragma once

#include "ui/elements/element.h"
#include "ui/color.h"

namespace ui {
	class BackgroundAware : virtual public Element {
		public:
			const Color &getBackground() const {
				return _background;
			}

			void setBackground(const Color &value) {
				_background = value;
			}

		private:
			Color _background = Color::black;
	};
}
