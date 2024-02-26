#pragma once

#include "container.h"

namespace ui {
	class Workspace : public Container {
		public:
			explicit Workspace(Size& size) {
				setSize(size);
			}

			void measure() {
				Element::measure(Rectangle(getSize()));
			}

			void arrange() {
				Element::arrange(Rectangle(getSize()));
			}
	};
}