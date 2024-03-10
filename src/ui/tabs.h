#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/tab_bar.h"
#include "grafica/elements/image.h"
#include "grafica/elements/linear_gradient_view.h"
#include "resources/images.h"

#include "tab_item_view.h"
#include "gradient/tab_view.h"
#include "flame/tab_view.h"
#include "wave/tab_view.h"
#include "piano/tab_view.h"
#include "strobe/tab_view.h"

using namespace grafica;
using namespace resources::images;

namespace ui {
	class PianoTabBar : public TabBar {
		public:
			TabItemView gradientItemView = TabItemView(&gradientOn, &gradientOff);
			GradientTabView gradientTabView = GradientTabView();

			TabItemView waveItemView = TabItemView(&waveOn, &waveOff);
			WaveTabView waveTabView = WaveTabView();

			TabItemView flameItemView = TabItemView(&flameOn, &flameOff);
			FlameTabView flameTabView = FlameTabView();

			TabItemView strobeItemView = TabItemView(&strobeOn, &strobeOff);
			StrobeTabView strobeTabView = StrobeTabView();

			TabItemView pianoItemView = TabItemView(&pianoOn, &pianoOff);
			PianoTabView pianoTabView = PianoTabView();

			PianoTabBar() {
				this->addTabAndView(&gradientItemView, &gradientTabView);
				this->addTabAndView(&waveItemView, &waveTabView);
				this->addTabAndView(&flameItemView, &flameTabView);
				this->addTabAndView(&strobeItemView, &strobeTabView);
				this->addTabAndView(&pianoItemView, &pianoTabView);
				this->setSelectedIndex(0);
			}
	};
}