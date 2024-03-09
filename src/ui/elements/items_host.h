#pragma once

#include "layout.h"
#include "vector"

namespace ui {
	template<typename TItem, typename TItemView>
	class ItemsHost : public Layout {
		public:
			size_t getItemsCount() {
				return _items.size();
			}

			TItem getItemAt(size_t index) {
				return _items[index];
			}

			void addItem(const TItem& item) {
				_items.push_back(item);

				if (_itemViewsLayout) {
					auto view = createItemView();
					auto viewElement = reinterpret_cast<Element*>(view);

					viewElement->addEventHandler([this, view](TouchEvent& event) {
						auto index = _itemViewsLayout->getIndexOfChild(view);
						setSelectedIndex(index);
					});

					itemToView(item, view);
					_itemViewsLayout->addChild(view);
				}
			}

			size_t getSelectedIndex() const {
				return _selectedIndex;
			}

			void setSelectedIndex(int32_t value) {
				if (value == _selectedIndex)
					return;

				_selectedIndex = value;

				for (size_t i = 0; i < _itemViewsLayout->getChildrenCount(); i++) {
					setItemViewSelected(reinterpret_cast<TItemView*>(_itemViewsLayout->getChildAt(i)), i == value);
				}

				onSelectionChanged();

				_selectionChanged.invoke();
			}

			void addOnSelectionChanged(const std::function<void()>& value) {
				_selectionChanged.add(value);
			}

		protected:
			virtual TItemView* createItemView() = 0;

			virtual void itemToView(const TItem& item, TItemView* view) = 0;

			virtual void setItemViewSelected(TItemView* element, const bool& value) = 0;

			virtual void onSelectionChanged() {

			}

		public:
			Layout* getItemViewsLayout() const {
				return _itemViewsLayout;
			}

			void setItemViewsLayout(Layout *itemsLayout) {
				_itemViewsLayout = itemsLayout;
			}

		private:
			Layout* _itemViewsLayout = nullptr;
			std::vector<TItem> _items {};
			size_t _selectedIndex = -1;
			Action<> _selectionChanged;
	};
}