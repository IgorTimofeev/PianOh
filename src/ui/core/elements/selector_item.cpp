#include "selector_item.h"
#include "selector.h"

namespace ui {
	bool SelectorItem::onEvent(TouchEvent &event) {
		Layout::onEvent(event);

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