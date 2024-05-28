#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/text.h"
#include "grafica/elements/rectangle.h"
#include "ui/tabs/tab.h"
#include "devices/piano/effects/strobe_effect.h"

using namespace grafica;
using namespace devices;

namespace ui {
	class StrobeTab : public Tab {
		public:
			StrobeTab() {
				setEffect(&strobeEffect);

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

			StrobeEffect strobeEffect = StrobeEffect(Color::white);
	};
}