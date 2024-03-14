#pragma once

#include "Arduino.h"

#include "grafica/elements/stack_layout.h"
#include "grafica/gradient.h"
#include "grafica/elements/linear_gradient_view.h"
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
				rows.setSpacing(50);

				gradient.addRainbowStops();

				gradientView.setGradient(&gradient);
				gradientView.setSize(Size(piano.getSize().getWidth(), 20));
				rows.addChild(&gradientView);

				gradientEffect.setGradient(&gradient);
				piano.setEffect(&gradientEffect);
				rows.addChild(&piano);

				addChild(&rows);
			}

			StackLayout rows = StackLayout();
			Piano piano = Piano();
			LinearGradient gradient = LinearGradient();
			LinearGradientView gradientView = LinearGradientView();
			devices::GradientEffect gradientEffect = devices::GradientEffect();

			Effect* getEffect() const {
				return (Effect*) &gradientEffect;
			}
	};
}