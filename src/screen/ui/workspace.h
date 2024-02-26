#pragma once

#include "container.h"

namespace ui {
	class Workspace : public Container {
		public:
			void measure() {
				Element::measure(Bounds(getSize()));
			}

			void arrange() {
				Element::arrange(Bounds(getSize()));
			}
	};
}