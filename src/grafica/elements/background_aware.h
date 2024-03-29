#pragma once

#include "element.h"
#include "grafica/color.h"

namespace grafica {
	class BackgroundAware : public virtual Element {
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
