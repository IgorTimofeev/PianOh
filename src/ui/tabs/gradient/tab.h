#pragma once

#include "Arduino.h"

#include "grafica/elements/stack_layout.h"
#include "grafica/gradient.h"
#include "ui/elements/piano/gradient_selector.h"
#include "ui/elements/piano/piano.h"
#include "ui/tabs/tab.h"
#include "devices/piano/effects/gradient_effect.h"

using namespace grafica;
using namespace devices;

namespace ui {
	class GradientTab : public Tab {
		public:
			GradientTab() {
				rows.setAlignment(Alignment::center);

				gradient.addRainbowStops();
				gradientEffect.setGradient(&gradient);
				setEffect(&gradientEffect);

				piano.setHorizontalAlignment(Alignment::center);
				piano.setEffect(getEffect());
				rows.addChild(&piano);

				gradientSelector.setHorizontalAlignment(Alignment::center);
				gradientSelector.setGradient(&gradient);
				gradientSelector.setSize(Size(piano.keysWidth, 40));
				gradientSelector.setGripRadius(8);
				rows.addChild(&gradientSelector);

				addChild(&rows);
			}

			StackLayout rows = StackLayout();
			ui::Piano piano = ui::Piano();
			LinearGradient gradient = LinearGradient();
			GradientSelector gradientSelector = GradientSelector();

			devices::GradientEffect gradientEffect = devices::GradientEffect();
	};
}