#pragma once

#include "grafica/elements/stack_layout.h"

using namespace grafica;

namespace ui {
	class Rows : public StackLayout {
		public:
			Rows() {
				setSpacing(10);
			}
	};
}