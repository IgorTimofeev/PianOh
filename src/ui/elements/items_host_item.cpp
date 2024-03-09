#include "items_host_item.h"
#include "items_host.h"

namespace ui {
	bool ItemsHostItem::onEvent(TouchEvent &event) {
		Layout::onEvent(event);

		if (getItemsHost())
			getItemsHost()->setSelectedIndex(getItemsHost()->getIndexOfItem(this));

		return true;
	}

	void ItemsHostItem::setSelected(const bool &value) {

	}

	ItemsHost *ItemsHostItem::getItemsHost() const {
		return _itemsHost;
	}

	void ItemsHostItem::setItemsHost(ItemsHost *itemsHost) {
		_itemsHost = itemsHost;
	}
}