#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/selector.h"
#include "grafica/elements/selector_item.h"
#include "grafica/elements/image.h"
#include "grafica/elements/linear_gradient_view.h"

#include "tab_item_view.h"

#include "ui/tabs/gradient/tab_view.h"
#include "ui/tabs/flame/tab_view.h"
#include "ui/tabs/wave/tab_view.h"
#include "ui/tabs/piano/tab_view.h"
#include "ui/tabs/strobe/tab_view.h"
#include "ui/elements/piano/piano.h"

#include "resources/images.h"

using namespace grafica;
using namespace resources::images;

namespace ui {
	class TabBar : public Selector {
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

			TabBar() {
				// Background
				addChild(&_background);

				auto tmpLeftSize = 52;

				// Left

				// Background
				_itemsLayoutHolder.setSize(Size(tmpLeftSize, Size::calculated));
				_itemsLayoutHolder.addChild(&_itemsLayoutBackground);

				// Items
				_itemsLayout.setSpacing(0);
				_itemsLayoutHolder.addChild(&_itemsLayout);
				setItemsLayout(&_itemsLayout);

				addChild(&_itemsLayoutHolder);

				// Right
				_viewLayout.setMargin(Margin(tmpLeftSize, 0, 0, 0));
				addChild(&_viewLayout);

				// Initialization
				addTabAndView(&gradientItemView, &gradientTabView);
				addTabAndView(&waveItemView, &waveTabView);
				addTabAndView(&flameItemView, &flameTabView);
				addTabAndView(&strobeItemView, &strobeTabView);
				addTabAndView(&pianoItemView, &pianoTabView);
				setSelectedIndex(0);
			}

		protected:
			void onSelectionChanged() override {
				_viewLayout.removeChildren();

				if (getSelectedIndex() >= 0)
					_viewLayout.addChild(_views[getSelectedIndex()]);
			}

		private:
			Layout _itemsLayoutHolder = Layout();
			Rectangle _itemsLayoutBackground = Rectangle(Color::black);
			StackLayout _itemsLayout = StackLayout();

			Rectangle _background = Rectangle(Color::white);
			Layout _viewLayout = Layout();

			std::vector<Element*> _views {};

			void addTabAndView(SelectorItem* tab, Element* view) {
				_views.push_back(view);
				addItem(tab);
			}
	};
}