#pragma once

#include "Arduino.h"
#include "ui/tabs/effect_tab.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/button.h"
#include "grafica/animation.h"

using namespace grafica;

namespace ui {
	class PianoTab : public EffectTab {
		public:
			PianoTab() {
				setAlignment(Alignment::center);

				button.setSize(Size(120, 40));
				button.setAlignment(Alignment::center, Alignment::center);
				button.setBackground(Color::gold);
				button.setForeground(Color::main1);
				button.setText("Click");

				button.addOnClick([this](Event& event) {
					button.startAnimation(new SizeAnimation(
						pizda ? Size(320, 100) : Size(120, 40),
						pizda ? Size(120, 40) : Size(320, 100),
						200000,
						[this](const Size& size) {
							button.setSize(size);
						}
					));

					pizda = !pizda;
				});

				addChild(&button);
			}

			bool pizda = false;
			Button button = Button();
	};
}