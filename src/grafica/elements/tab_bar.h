#pragma once

#include "selector.h"
#include "selector_item.h"

namespace grafica {
	class TabBar : public Selector {
		public:
			TabBar() {
				// Background
				this->addChild(new Rectangle(Color::white));

				auto pizda = 52;

				// Left

				// Background
				_itemsLayoutHolder.setSize(Size(pizda, Size::calculated));
				_itemsLayoutHolder.addChild(&_itemsLayoutBackground);

				// Items
				_itemsLayout.setSpacing(0);
				_itemsLayoutHolder.addChild(&_itemsLayout);
				this->setItemsLayout(&_itemsLayout);

				this->addChild(&_itemsLayoutHolder);

				// Right
				_viewLayout.setMargin(Margin(pizda, 0, 0, 0));
				this->addChild(&_viewLayout);
			}

			void addTabAndView(SelectorItem* tab, Element* view) {
				_views.push_back(view);
				this->addItem(tab);
			}

		protected:
			void onSelectionChanged() override {
				_viewLayout.removeChildren();

				if (this->getSelectedIndex() >= 0)
					_viewLayout.addChild(_views[this->getSelectedIndex()]);
			}

		private:
			Layout _itemsLayoutHolder = Layout();
			Rectangle _itemsLayoutBackground = Rectangle(Color::black);
			StackLayout _itemsLayout = StackLayout();
			Layout _viewLayout = Layout();

			std::vector<Element*> _views {};
	};
}