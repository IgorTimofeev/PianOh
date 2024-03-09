#pragma once

#include "items_host.h"

namespace ui {
	template<typename TItem, typename TTemplate>
	class TabBar : public ItemsHost<TItem, TTemplate> {
		public:
			TabBar() {
				_itemsLayout->setSpacing(0);
				_itemsLayout->setSize(Size(100, Size::calculated));
				this->addChild(_itemsLayout);

				_viewLayout->setMargin(Margin(100, 0, 0, 0));
				this->addChild(_viewLayout);

				this->setItemViewsLayout(_itemsLayout);
			}

			~TabBar() override {
				delete _itemsLayout;
				delete _viewLayout;
			}

			void addTabAndView(const TItem& tab, Element* view) {
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