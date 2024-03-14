#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/slider.h"
#include "grafica/elements/text.h"

using namespace grafica;

namespace ui {
	class WaveTab : public StackLayout {
		public:
			WaveTab() {
				setAlignment(Alignment::center);

				// Slider
				slider.setCornerRadius(5);
				slider.setValue(0.7);
				slider.setSize(Size(150, 40));

				addChild(&slider);

				// Text
				text.setText("Initial text");
				addChild(&text);

				slider.addOnValueChanged([this]() {
					text.setText(String("Value: ") + slider.getValue());
				});
			}

			Slider slider = Slider();
			Text text = Text();
	};
}