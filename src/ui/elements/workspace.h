#pragma once

#include "layout.h"

namespace ui {
	class Workspace : public Layout {
		public:
			void measure() {
				Element::measure(getSize());
			}

			void arrange() {
				Element::arrange(Bounds(getSize()));
			}
	};
}