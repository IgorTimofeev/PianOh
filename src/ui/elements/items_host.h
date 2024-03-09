#pragma once

#include "layout.h"
#include "vector"

namespace ui {
	class ItemsHostItem;

	class ItemsHost : public Layout {
		public:
			size_t getItemsCount();

			ItemsHostItem* getItemAt(size_t index);

			size_t getIndexOfItem(ItemsHostItem* item);

			void addItem(ItemsHostItem* item);

			size_t getSelectedIndex() const;

			void setSelectedIndex(size_t value);

			void addOnSelectionChanged(const std::function<void()>& value) {
				_selectionChanged.add(value);
			}

			void setItemsLayout(Layout* layout);

		protected:
			virtual void onSelectionChanged();

		private:
			Layout* _itemsLayout = nullptr;
			size_t _selectedIndex = -1;
			Action<> _selectionChanged = Action<>();
	};
}