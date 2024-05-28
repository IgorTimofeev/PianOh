#pragma once

#include "Arduino.h"

#include "grafica/elements/layout.h"
#include "grafica/elements/seven_segment.h"
#include "grafica/elements/slider.h"
#include "grafica/elements/text.h"

#include "ui/tabs/tab.h"
#include "ui/elements/titler.h"
#include "ui/elements/rows.h"

#include "devices/piano/effects/flame_effect.h"

using namespace grafica;
using namespace devices;

namespace ui {
	class FlameTab : public Tab {
		public:
			FlameTab() {
				setAlignment(Alignment::center);

				setEffect(&flameEffect);

				backgroundSlider.setCornerRadius(5);
				backgroundSlider.setValue(0);
				backgroundSlider.setSize(Size(150, 40));

				backgroundSlider.addOnValueChanged([this]() {
					Color color = Color::gold;
					color.multiply(backgroundSlider.getValue() * 0.1f);
					flameEffect.setBackgroundColor(color);
				});

				backgroundTitler.addChild(&backgroundSlider);

				rows.addChild(&backgroundTitler);

				addChild(&rows);
			}

			FlameEffect flameEffect = FlameEffect();

			Rows rows = Rows();

			Titler backgroundTitler = Titler("Background");
			Slider backgroundSlider = Slider();
	};
}