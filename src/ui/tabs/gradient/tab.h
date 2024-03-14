#pragma once

#include "Arduino.h"

#include "grafica/elements/stack_layout.h"
#include "grafica/elements/linear_gradient_view.h"

#include "ui/elements/piano/piano.h"
#include "ui/tabs/effect_tab.h"

using namespace grafica;

namespace ui {
	class GradientTab : public EffectTab {
		public:
			GradientTab() {
				rows.setAlignment(Alignment::center);
				rows.setSpacing(50);

				gradientView.setSize(Size(piano.getSize().getWidth(), 20));
				rows.addChild(&gradientView);

				rows.addChild(&piano);

				addChild(&rows);
			}

			StackLayout rows = StackLayout();
			Piano piano = Piano();
			LinearGradientView gradientView = LinearGradientView();
	};
}