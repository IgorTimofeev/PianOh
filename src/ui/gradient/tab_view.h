#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/linear_gradient_view.h"
#include "../piano.h"

using namespace grafica;

namespace ui {
	class GradientTabView : public StackLayout {
		public:
			GradientTabView() {
				setAlignment(Alignment::center);

				gradientView.setSize(Size(300, 50));
				gradientView.setMargin(Margin(20));
				addChild(&gradientView);

				addChild(&piano);
			}

			Piano piano = Piano();
			LinearGradientView gradientView = LinearGradientView();
	};
}