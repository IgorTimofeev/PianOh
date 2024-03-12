#include "selector_item.h"
#include "selector.h"

namespace grafica {
	bool SelectorItem::onEvent(Event &event) {
		Layout::onEvent(event);

		if (event.getType() != EventType::touchDown && event.getType() != EventType::touchDrag)
			return false;

		if (getSelector())
			getSelector()->setSelectedIndex(getSelector()->getIndexOfItem(this));

		return true;
	}

	void SelectorItem::setSelected(const bool &value) {

	}

	Selector *SelectorItem::getSelector() const {
		return _selector;
	}

	void SelectorItem::setSelector(Selector *value) {
		_selector = value;
	}
}