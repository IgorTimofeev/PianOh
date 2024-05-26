#pragma once

#include "grafica/elements/layout.h"
#include "devices/piano/effects/effect.h"

using namespace grafica;
using namespace devices;

namespace ui {
	class Tab : public Layout {
		public:
			Effect* setEffect(Effect* value) {
				return _effect = value;
			}

			Effect* getEffect() {
				return _effect;
			}

		private:
			Effect* _effect = nullptr;
	};
}