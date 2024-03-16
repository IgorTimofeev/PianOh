#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/slider.h"
#include "grafica/elements/text.h"
#include "ui/tabs/effect_tab.h"
#include "grafica/elements/stack_layout.h"
#include "ui/piano_application.h"

using namespace grafica;

namespace ui {
	class WaveTab : public EffectTab {
		public:
			WaveTab() {
				rows.setAlignment(Alignment::center);

				// Brightness
				brightnessSlider.setCornerRadius(5);
				brightnessSlider.setValue(0.7);
				brightnessSlider.setSize(Size(150, 40));

				brightnessSlider.addOnValueChanged([this]() {
					PianoApplication::getInstance()._display.setBrightness((uint8_t) (brightnessSlider.getValue() * 255.0f));
					brightnessText.setText(String("Brightness: ") + (uint8_t) (brightnessSlider.getValue() * 100.0f) + String("%"));
				});

				rows.addChild(&brightnessSlider);
				rows.addChild(&brightnessText);

				addChild(&rows);
			}

			StackLayout rows = StackLayout();

			Slider brightnessSlider = Slider();
			Text brightnessText = Text();
	};
}