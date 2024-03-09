#pragma once

#include "items_host.h"

namespace ui {
	template<typename TItem, typename TTemplate>
	class TabBar : public ItemsHost<TItem, TTemplate> {
		public:
			TabBar() {
				// Left
				auto leftLayout = new Layout();

				// Background
				leftLayout->setSize(Size(100, Size::calculated));
				leftLayout->addChild(new Rectangle(Color::gray));

				_itemsLayout->setMargin(Margin(10));
				leftLayout->addChild(_itemsLayout);

				this->addChild(leftLayout);

				_viewLayout->setMargin(Margin(100, 0, 0, 0));
				this->addChild(_viewLayout);

				this->setItemViewsLayout(_itemsLayout);
			}

			~TabBar() override {
				delete _itemsLayout;
				delete _viewLayout;
			}

			void addTabAndView(const TItem& tab, Element* view) {
				_tabsAndViews.push_back(std::pair<TItem, Element*>(tab, view));
				this->addItem(tab);
			}

		protected:


			void onSelectionChanged() override {
				_viewLayout->removeChildren();

				if (this->getSelectedIndex() < 0)
					return;

				_viewLayout->addChild(_tabsAndViews[this->getSelectedIndex()].second);
			}

		private:
			StackLayout* _itemsLayout = new StackLayout();
			Layout* _viewLayout = new Layout();

			std::vector<std::pair<TItem, Element*>> _tabsAndViews {};
	};
}