#pragma once

#include "grafica/elements/layout.h"
#include "devices/piano/effects/effect.h"

using namespace grafica;
using namespace devices;

namespace ui {
	class EffectTab : public Layout {
		public:
			virtual Effect* getEffect() {
				return nullptr;
			}
	};
}