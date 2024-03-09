#include "items_host.h"
#include "items_host_item.h"
#include "functional"

namespace ui {
	ItemsHostItem *ItemsHost::getItemAt(size_t index) {
		return
			_itemsLayout
			? reinterpret_cast<ItemsHostItem*>(_itemsLayout->getChildAt(index))
			: nullptr;
	}

	size_t ItemsHost::getIndexOfItem(ItemsHostItem* item) {
		return
			_itemsLayout
			? _itemsLayout->getIndexOfChild(item)
			: -1;
	}

	void ItemsHost::addItem(ItemsHostItem* item) {
		if (!_itemsLayout)
			return;

		item->setItemsHost(this);
		_itemsLayout->addChild(item);
	}

	size_t ItemsHost::getSelectedIndex() const {
		return _selectedIndex;
	}

	void ItemsHost::setSelectedIndex(size_t value) {
		if (value == _selectedIndex || !_itemsLayout)
			return;

		_selectedIndex = value;

		for (size_t i = 0; i < _itemsLayout->getChildrenCount(); i++) {
			reinterpret_cast<ItemsHostItem*>(_itemsLayout->getChildAt(i))->setSelected(i == value);
		}

		onSelectionChanged();

		_selectionChanged.invoke();
	}

	void ItemsHost::onSelectionChanged() {

	}

	size_t ItemsHost::getItemsCount() {
		return _itemsLayout ? _itemsLayout->getChildrenCount() : 0;
	}

	void ItemsHost::setItemsLayout(Layout *layout) {
		_itemsLayout = layout;
	}
}