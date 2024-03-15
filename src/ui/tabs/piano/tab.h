#pragma once

#include "Arduino.h"
#include "ui/tabs/effect_tab.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/button.h"
#include "grafica/animations/size_animation.h"

using namespace grafica;

namespace ui {
	class PianoTab : public EffectTab {
		public:
			PianoTab() {
				setAlignment(Alignment::center);

				button.setSize(Size(120, 40));
				button.setAlignment(Alignment::center, Alignment::center);
				button.setBackground(Color::gold);
				button.setForeground(Color::black);
				button.setText("Click");

				button.addOnClick([this](Event& event) {
					auto animation = new SizeAnimation(
						pizda ? Size(320, 100) : Size(120, 40),
						pizda ? Size(120, 40) : Size(320, 100),
						200000
					);

					button.addAnimation(animation);

					animation->start();

					animation->addOnCompleted([animation]() {
						delete animation;
					});

					pizda = !pizda;
				});

				addChild(&button);
			}

			bool pizda = false;
			Button button = Button();
	};
}