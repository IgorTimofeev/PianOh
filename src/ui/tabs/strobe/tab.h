#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/text.h"
#include "grafica/elements/rectangle.h"
#include "ui/tabs/effect_tab.h"

using namespace grafica;

namespace ui {
	class StrobeTab : public EffectTab {
		public:
			StrobeTab() {
				setAlignment(Alignment::center);

				addChild(&rectangle);

				text.setAlignment(Alignment::center, Alignment::center);
				text.setMargin(Margin(10));
				text.setForeground(Color::black);
				text.setText("Timer");
				addChild(&text);
			}

			Rectangle rectangle = Rectangle(Color::gold);
			Text text = Text();
	};
}