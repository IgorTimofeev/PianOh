#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/slider.h"
#include "grafica/elements/stack_layout.h"
#include "grafica/elements/text.h"
#include "ui/tabs/tab.h"
#include "ui/piano_application.h"
#include "devices/piano/effects/water_effect.h"

using namespace grafica;
using namespace devices;

namespace ui {
	class WaveTab : public Tab {
		public:
			WaveTab() {
				rows.setAlignment(Alignment::center);

				setEffect(&waterEffect);

				// Brightness
				brightnessSlider.setCornerRadius(5);
				brightnessSlider.setValue(0.7);
				brightnessSlider.setSize(Size(150, 40));

				brightnessSlider.addOnValueChanged([this]() {
					PianoApplication::getInstance().getScreen().setBrightness((uint8_t) (brightnessSlider.getValue() * 255.0f));
					brightnessText.setText(String("Brightness: ") + (uint8_t) (brightnessSlider.getValue() * 100.0f) + String("%"));
				});

				rows.addChild(&brightnessSlider);
				rows.addChild(&brightnessText);

				addChild(&rows);
			}

			StackLayout rows = StackLayout();

			Slider brightnessSlider = Slider();
			Text brightnessText = Text();

			WaterEffect waterEffect = WaterEffect();
	};
}