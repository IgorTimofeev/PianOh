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

				holder.setMargin(Margin(10));
				holder.setAlignment(Alignment::center);
				addChild(&holder);

				holder.addChild(&holderBack);

				text.setAlignment(Alignment::center);
//				text.setMargin(Margin(10));
				text.setForeground(Color::main1);
				text.setText("Timer");
				holder.addChild(&text);
			}

			Layout holder = Layout();
			Rectangle holderBack = Rectangle(Color::water);

			Rectangle rectangle = Rectangle(Color::gold);
			Text text = Text();
	};
}