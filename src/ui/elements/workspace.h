#pragma once

#include "layout.h"

namespace ui {
	class Workspace : public Layout {
		public:
			void measure(Display& display) {
				Element::measure(display, getSize());
			}

			void arrange() {
				Element::arrange(Bounds(getSize()));
			}
	};
}