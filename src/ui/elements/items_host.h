#pragma once

#include "layout.h"
#include "vector"

namespace ui {
	template<typename T>
	class ItemsHost : public Layout {
		public:
			size_t getItemsCount() {
				return _items.size();
			}

			T getItemAt(size_t index) {
				return _items[index];
			}

			void addItem(T item) {
				_items.push_back(item);

				if (_itemsLayout)
					_itemsLayout->addChild(itemToElement(item));
			}

			size_t getSelectedIndex() const {
				return _selectedIndex;
			}

			void setSelectedIndex(int32_t value) {
				if (value == _selectedIndex)
					return;

				_selectedIndex = value;

				for (size_t i = 0; i < _itemsLayout->getChildrenCount(); i++) {
					setItemSelected(_itemsLayout->getChildAt(i), i == value);
				}

				onSelectionChanged();

				_selectionChanged.invoke();
			}

			void addOnSelectionChanged(const std::function<void()>& value) {
				_selectionChanged.add(value);
			}

		protected:
			virtual Element* itemToElement(T item) {
				auto text = new Text();
				text->setColor(Color::white);
				text->setText("Penis");

				return text;
			}

			virtual void setItemSelected(Element* element, const bool& value) {
				reinterpret_cast<Text*>(element)->setColor(value ? Color::gold : Color::white);
			}

			virtual void onSelectionChanged() {

			}

		public:
			Layout* getItemsLayout() const {
				return _itemsLayout;
			}

			void setItemsLayout(Layout *itemsLayout) {
				_itemsLayout = itemsLayout;
			}

		private:
			Layout* _itemsLayout = nullptr;
			std::vector<T> _items {};
			size_t _selectedIndex = -1;
			Action<> _selectionChanged;
	};
}