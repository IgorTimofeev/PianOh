#pragma once

#include "selector.h"
#include "selector_item.h"

namespace ui {
	class TabBar : public Selector {
		public:
			TabBar() {
				_itemsLayout->setSpacing(0);
				_itemsLayout->setSize(Size(100, Size::calculated));
				this->addChild(_itemsLayout);
				this->setItemsLayout(_itemsLayout);

				_viewLayout->setMargin(Margin(100, 0, 0, 0));
				this->addChild(_viewLayout);
			}

			~TabBar() override {
				delete _itemsLayout;
				delete _viewLayout;
			}

			void addTabAndView(SelectorItem* tab, Element* view) {
				_views.push_back(view);
				this->addItem(tab);
			}

		protected:
			void onSelectionChanged() override {
				_viewLayout->removeChildren();

				if (this->getSelectedIndex() >= 0)
					_viewLayout->addChild(_views[this->getSelectedIndex()]);
			}

		private:
			StackLayout* _itemsLayout = new StackLayout();
			Layout* _viewLayout = new Layout();

			std::vector<Element*> _views {};
	};
}