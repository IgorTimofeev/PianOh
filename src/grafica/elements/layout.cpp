#include "layout.h"

namespace grafica {
	void Layout::render(Display &display) {
		for (auto child : *this) {
			child->setParent(this);
			child->setFirstParent(getFirstParent());
			child->render(display);
		}
	}

	bool Layout::onEvent(Event &event) {
		for (int32_t i = (int32_t) getChildrenCount() - 1; i >= 0; i--) {
			if (getChildAt(i)->handleEvent(event)) {
				return true;
			}
		}

		return false;
	}

	std::vector<Element *>::iterator Layout::begin() {
		return _children.begin();
	}

	std::vector<Element *>::iterator Layout::end() {
		return _children.end();
	}

	size_t Layout::getChildrenCount() {
		return _children.size();
	}

	int32_t Layout::getIndexOfChild(Element *element) {
		auto iterator = find(_children.begin(), _children.end(), element);

		if (iterator == _children.end()) {
			return -1;
		}
		else {
			return iterator - _children.begin();
		}
	}

	void Layout::removeChildAt(int index) {
		_children.erase(_children.begin() + index);

		invalidate();
	}

	void Layout::removeChild(Element *child) {
		auto iterator = std::find(_children.begin(), _children.end(), child);

		if (iterator == _children.end())
			return;

		_children.erase(iterator);

		invalidate();
	}

	void Layout::removeChildren() {
		_children.clear();

		invalidate();
	}

	Element *Layout::getChildAt(size_t index) {
		return _children[index];
	}

	void Layout::addChild(Element *child) {
		child->setParent(this);
		child->setFirstParent(getFirstParent());

		_children.push_back(child);

		invalidate();
	}

	Element *Layout::operator[](size_t index) {
		return getChildAt(index);
	}

	void Layout::operator+=(Element *child) {
		addChild(child);
	}

	void Layout::operator-=(Element *child) {
		removeChild(child);
	}

	Size Layout::onMeasure(Display &display, const Size &availableSize) {
		auto result = Size();

		Size childSize;

		for (auto child : *this) {
			childSize = child->measure(display, availableSize);

			if (childSize.getWidth() > result.getWidth())
				result.setWidth(childSize.getWidth());

			if (childSize.getHeight() > result.getHeight())
				result.setHeight(childSize.getHeight());
		}

		return result;
	}

	void Layout::onArrange(const Bounds &bounds) {
		for (auto child : *this) {
			child->arrange(bounds);
		}
	}
}