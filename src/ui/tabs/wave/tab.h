#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/slider.h"
#include "grafica/elements/text.h"
#include "ui/tabs/effect_tab.h"
#include "grafica/elements/stack_layout.h"

using namespace grafica;

namespace ui {
	class WaveTab : public EffectTab {
		public:
			WaveTab() {
				rows.setAlignment(Alignment::center);

				// Slider
				slider.setCornerRadius(5);
				slider.setValue(0.7);
				slider.setSize(Size(150, 40));

				rows.addChild(&slider);

				// Text
				text.setText("Initial text");
				rows.addChild(&text);

				addChild(&rows);

				slider.addOnValueChanged([this]() {
					text.setText(String("Value: ") + slider.getValue());
				});
			}

			StackLayout rows = StackLayout();
			Slider slider = Slider();
			Text text = Text();
	};
}