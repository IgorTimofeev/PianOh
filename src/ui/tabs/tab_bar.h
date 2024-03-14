#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/selector.h"
#include "grafica/elements/selector_item.h"
#include "grafica/elements/image.h"
#include "grafica/elements/linear_gradient_view.h"
#include "grafica/animations/margin_animation.h"

#include "tab_item.h"

#include "ui/elements/piano/piano.h"

#include "ui/tabs/gradient/tab.h"
#include "ui/tabs/flame/tab.h"
#include "ui/tabs/wave/tab.h"
#include "ui/tabs/piano/tab.h"
#include "ui/tabs/strobe/tab.h"
#include "ui/application.h"

#include "resources/images.h"

using namespace grafica;
using namespace resources::images;

namespace ui {
	class TabBar : public Selector {
		public:
			TabItem gradientItemView = TabItem(&gradientOn, &gradientOff, "Gradient");
			GradientTab gradientTabView = GradientTab();

			TabItem waveItemView = TabItem(&waveOn, &waveOff, "Wave");
			WaveTab waveTabView = WaveTab();

			TabItem flameItemView = TabItem(&flameOn, &flameOff, "Flame");
			FlameTab flameTabView = FlameTab();

			TabItem strobeItemView = TabItem(&strobeOn, &strobeOff, "Strobe");
			StrobeTab strobeTabView = StrobeTab();

			TabItem pianoItemView = TabItem(&pianoOn, &pianoOff, "Settings");
			PianoTab pianoTabView = PianoTab();

			TabBar() {
				addChild(&_background);
				addChild(&_tabLayout);

				// Menu button
				_menuButton.setSize(Size(40, 40));
				_menuButton.setAlignment(Alignment::start, Alignment::start);
				_menuButton.setBackground(Color::white);
				_menuButton.setFontSize(4);
				_menuButton.setText("=");

				_menuButton.addOnClick([this](Event& event) {
					setMenuOpen(true);
				});

				addChild(&_menuButton);

				// Menu background
//				_menuOverlay.setVisible(false);
				addChild(&_menuOverlay);

				_menuOverlay.addEventHandler([this](Event& event) {
					if (event.getType() != EventType::touchDown)
						return;

					setMenuOpen(false);
					event.setHandled(true);
				});

				// Menu
				_menu.setSize(Size(_menuSize, Size::calculated));
				_menu.setMargin(Margin(-15, 0, 0, 0));
//				_menu.setVisible(false);
				_menu.addChild(&_menuBackground);

				_menuItemsLayout.setMargin(Margin(10));
				_menuItemsLayout.setSpacing(10);
				_menu.addChild(&_menuItemsLayout);
				setItemsLayout(&_menuItemsLayout);

				addChild(&_menu);

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
				_tabLayout.removeChildren();

				if (getSelectedIndex() < 0)
					return;

				auto& tab = _views[getSelectedIndex()];

				Application::getInstance().piano.setEffect(tab->getEffect());

				_tabLayout.addChild(tab);
			}

		private:
			Rectangle _background = Rectangle(Color::white);
			Layout _tabLayout = Layout();

			Button _menuButton = Button();
			Element _menuOverlay = Element();
			const uint16_t _menuSize = 180;
			Layout _menu = Layout();
			Rectangle _menuBackground = Rectangle(Color::black);
			StackLayout _menuItemsLayout = StackLayout();

			std::vector<EffectTab*> _views {};

			void addTabAndView(SelectorItem* tab, EffectTab* view) {
				_views.push_back(view);
				addItem(tab);
			}

			void setMenuOpen(bool value) {
				_menuOverlay.setVisible(value);
				_menu.setVisible(value);

//				if (value) {
//					_menuOverlay.setVisible(true);
//					_menu.setVisible(true);
//				}
//
//				auto animation = new MarginAnimation(
//					Margin(value ? -_menuSize : 0, 0, 0, 0),
//					Margin(value ? 0 : -_menuSize, 0, 0, 0),
//					5000
//				);
//
//				animation->addOnCompleted([this, value, animation] {
//					if (!value) {
//						_menuOverlay.setVisible(false);
//						_menu.setVisible(false);
//					}
//
//					delete animation;
//				});
//
//				_menu.addAnimation(animation);
//
//				animation->start();
			}
	};
}