#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/seven_segment.h"
#include "grafica/elements/slider.h"
#include "grafica/elements/text.h"
#include "ui/tabs/tab.h"
#include "devices/piano/effects/flame_effect.h"

using namespace grafica;
using namespace devices;

namespace ui {
	class FlameTab : public Tab {
		public:
			FlameTab() {
				setAlignment(Alignment::center);

				setEffect(&flameEffect);

				rows.setSpacing(5);

				rows.addChild(&backgroundText);

				backgroundSlider.setCornerRadius(5);
				backgroundSlider.setValue(0);
				backgroundSlider.setSize(Size(150, 40));

				backgroundSlider.addOnValueChanged([this]() {
					Color color = Color::gold;
					color.multiply(backgroundSlider.getValue() * 0.2f);
					flameEffect.setBackgroundColor(color);
				});

				rows.addChild(&backgroundSlider);

				addChild(&rows);
			}

			FlameEffect flameEffect = FlameEffect();

			StackLayout rows = StackLayout();

			Slider backgroundSlider = Slider();
			Text backgroundText = Text("Background");
	};
}