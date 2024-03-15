#pragma once

#include "Arduino.h"

#include "grafica/elements/stack_layout.h"
#include "grafica/gradient.h"
#include "ui/elements/piano/gradient_selector.h"
#include "devices/piano/effects/gradient_effect.h"
#include "ui/elements/piano/piano.h"
#include "ui/tabs/effect_tab.h"

using namespace grafica;
using namespace devices;

namespace ui {
	class GradientTab : public EffectTab {
		public:
			GradientTab() {
				rows.setAlignment(Alignment::center);

				gradient.addRainbowStops();

				gradientEffect.setGradient(&gradient);

				piano.setHorizontalAlignment(Alignment::center);
				piano.setEffect(&gradientEffect);
				rows.addChild(&piano);

				gradientSelector.setHorizontalAlignment(Alignment::center);
				gradientSelector.setGradient(&gradient);
				gradientSelector.setSize(Size(piano.keysWidth, 40));
				gradientSelector.setGripRadius(8);
				rows.addChild(&gradientSelector);

				addChild(&rows);
			}

			StackLayout rows = StackLayout();
			Piano piano = Piano();
			LinearGradient gradient = LinearGradient();
			GradientSelector gradientSelector = GradientSelector();
			devices::GradientEffect gradientEffect = devices::GradientEffect();

			Effect* getEffect() const {
				return (Effect*) &gradientEffect;
			}
	};
}