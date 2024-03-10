#include "selector.h"
#include "selector_item.h"

namespace ui {
	SelectorItem *Selector::getItemAt(size_t index) {
		return
			_itemsLayout
			? reinterpret_cast<SelectorItem*>(_itemsLayout->getChildAt(index))
			: nullptr;
	}

	size_t Selector::getIndexOfItem(SelectorItem* item) {
		return
			_itemsLayout
			? _itemsLayout->getIndexOfChild(item)
			: -1;
	}

	void Selector::addItem(SelectorItem* item) {
		if (!_itemsLayout)
			return;

		item->setSelector(this);
		_itemsLayout->addChild(item);
	}

	int32_t Selector::getSelectedIndex() const {
		return _selectedIndex;
	}

	void Selector::setSelectedIndex(int32_t value) {
		if (value == _selectedIndex || !_itemsLayout)
			return;

		_selectedIndex = value;

		for (size_t i = 0; i < _itemsLayout->getChildrenCount(); i++) {
			reinterpret_cast<SelectorItem*>(_itemsLayout->getChildAt(i))->setSelected(i == value);
		}

		onSelectionChanged();

		_selectionChanged.invoke();
	}

	void Selector::onSelectionChanged() {

	}

	size_t Selector::getItemsCount() {
		return _itemsLayout ? _itemsLayout->getChildrenCount() : 0;
	}

	void Selector::setItemsLayout(Layout *layout) {
		_itemsLayout = layout;
	}
}