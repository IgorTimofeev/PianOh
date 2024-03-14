#include "element.h"

namespace grafica {
	Size Element::measure(Display &display, const Size &availableSize) {
		auto desiredSize = onMeasure(display, availableSize);

		auto size = getSize();
		auto margin = getMargin();

		if (size.getWidth() != Size::calculated) {
			desiredSize.setWidth(size.getWidth());
		}

		if (size.getHeight() != Size::calculated) {
			desiredSize.setHeight(size.getHeight());
		}

		desiredSize.setWidth(desiredSize.getWidth() + margin.getLeft() + margin.getRight());
		desiredSize.setHeight(desiredSize.getHeight() + margin.getTop() + margin.getBottom());

		setDesiredSize(desiredSize);

		return desiredSize;
	}

	void Element::setDesiredSize(const Size &value) {
		_desiredSize = value;
	}

	void Element::setBounds(const Bounds &value) {
		_bounds = value;
	}

	void Element::onArrange(const Bounds &bounds) {

	}

	Size Element::onMeasure(Display &display, const Size &availableSize) {
		return {
			0,
			0,
		};
	}

	bool Element::onEvent(Event &event) {
		return false;
	}

	bool Element::handleEvent(Event &event) {
		if (!event.matches(this))
			return false;

		auto result = onEvent(event);

		_eventHandlers.invoke(event);

		return result;
	}

	void Element::addEventHandler(const std::function<void(Event &)> &handler) {
		_eventHandlers.add(handler);
	}

	void Element::setParent(Element *value) {
		_parent = value;
	}

	Element *Element::getParent() {
		return _parent;
	}

	void Element::setFirstParent(Element *value) {
		_firstParent = value;
	}

	Element *Element::getFirstParent() {
		return _firstParent;
	}

	const Bounds &Element::getBounds() {
		return _bounds;
	}

	const Size &Element::getDesiredSize() {
		return _desiredSize;
	}

	void Element::setSize(const Size &value) {
		_size = value;

		invalidate();
	}

	const Size &Element::getSize() {
		return _size;
	}

	void Element::setMargin(const Margin &value) {
		_margin = value;

		invalidate();
	}

	const Margin &Element::getMargin() {
		return _margin;
	}

	void Element::setAlignment(Alignment uniformValue) {
		setAlignment(uniformValue, uniformValue);
	}

	void Element::setAlignment(Alignment horizontal, Alignment vertical) {
		_horizontalAlignment = horizontal;
		_verticalAlignment = vertical;

		invalidate();
	}

	void Element::setVerticalAlignment(Alignment value) {
		_verticalAlignment = value;

		invalidate();
	}

	Alignment Element::getVerticalAlignment() const {
		return _verticalAlignment;
	}

	void Element::setHorizontalAlignment(Alignment value) {
		_horizontalAlignment = value;

		invalidate();
	}

	Alignment Element::getHorizontalAlignment() const {
		return _horizontalAlignment;
	}

	void Element::arrange(const Bounds &bounds) {
		auto margin = getMargin();
		auto desiredSize = getDesiredSize();
		auto size = getSize();

		Bounds newBounds;
		int32_t newPosition = 0;
		int32_t newSize = 0;

		calculateArrangeShit(
			getHorizontalAlignment(),
			bounds.getX(),
			size.getWidth(),
			desiredSize.getWidth(),
			margin.getLeft(),
			margin.getRight(),
			bounds.getWidth(),
			newPosition,
			newSize
		);

		newBounds.setX(newPosition);
		newBounds.setWidth(newSize);

		calculateArrangeShit(
			getVerticalAlignment(),
			bounds.getY(),
			size.getHeight(),
			desiredSize.getHeight(),
			margin.getTop(),
			margin.getBottom(),
			bounds.getHeight(),
			newPosition,
			newSize
		);

		if (tag == 1) {
			Serial.print(desiredSize.getHeight());
			Serial.print(" x ");
			Serial.print(bounds.getHeight());
			Serial.print(" x ");
			Serial.print(newPosition);
			Serial.print(" x ");
			Serial.println(newSize);
		}

		newBounds.setY(newPosition);
		newBounds.setHeight(newSize);

		setBounds(newBounds);
		onArrange(newBounds);
	}

	void Element::calculateArrangeShit(const Alignment &alignment, const int32_t &position, const uint16_t &size,
									   const uint16_t &desiredSize, const uint16_t &marginStart, const uint16_t &marginEnd,
									   const uint16_t &limit, int32_t &newPosition, int32_t &newSize) {
		switch (alignment) {
			case start:
				if (size == Size::calculated) {
					newSize = max(desiredSize - marginStart - marginEnd, 0);
				}
				else {
					newSize = size;
				}

				newPosition = position + marginStart;

				break;

			case center:
				if (size == Size::calculated) {
					newSize = max(desiredSize - marginStart - marginEnd, 0);
				}
				else {
					newSize = size;
				}

				newPosition = position + limit / 2 - newSize / 2 + marginStart - marginEnd;

				break;

			case end:
				if (size == Size::calculated) {
					newSize = max(desiredSize - marginStart - marginEnd, 0);
				}
				else {
					newSize = size;
				}

				newPosition = position + limit - marginEnd - newSize;

				break;

			case stretch:
				if (size == Size::calculated) {
					newSize = max(limit - marginStart - marginEnd, 0);
				}
				else {
					newSize = size;
				}

				newPosition = position + marginStart;

				break;
		}
	}

	void Element::invalidateRender() {
		if (_firstParent)
			_firstParent->invalidateRender();
	}

	void Element::invalidateLayout() {
		if (_firstParent)
			_firstParent->invalidateLayout();
	}

	void Element::invalidate() {
		if (_firstParent)
			_firstParent->invalidate();
	}

	void Element::tick() {

	}

	void Element::render(Display &display) {

	}
}