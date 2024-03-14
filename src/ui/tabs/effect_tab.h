#pragma once

#include "grafica/elements/layout.h"
#include "devices/piano/effects/effect.h"

using namespace grafica;
using namespace devices;

namespace ui {
	class EffectTab : public Layout {
		public:
			Effect* getEffect() const {
				return _effect;
			}

			void setEffect(Effect* effect) {
				_effect = effect;
			}

		private:
			Effect* _effect = nullptr;
	};
}