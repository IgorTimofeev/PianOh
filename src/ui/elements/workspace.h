#pragma once

#include "layout.h"

namespace ui {
	class Workspace : public Layout {
		public:
			void measure() {
				Element::measure(getSize());
			}

			void arrange() {
				auto size = getSize();
				auto bounds = Bounds(size);
				Element::arrange(bounds);
			}
	};
}