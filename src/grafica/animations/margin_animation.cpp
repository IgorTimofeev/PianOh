#include "Arduino.h"
#include "margin_animation.h"
#include "grafica/elements/element.h"

namespace grafica {
	MarginAnimation::MarginAnimation(const Margin &from, const Margin &to, uint32_t duration) {
		setFrom(from);
		setTo(to);
		setDuration(duration);
	}

	void MarginAnimation::onTick(Element *element, double position) {
		element->setMargin(Margin(
			(uint16_t) (_from.getLeft() + position * (_to.getLeft() - _from.getLeft())),
			(uint16_t) (_from.getTop() + position * (_to.getTop() - _from.getTop())),
			(uint16_t) (_from.getRight() + position * (_to.getRight() - _from.getRight())),
			(uint16_t) (_from.getBottom() + position * (_to.getBottom() - _from.getBottom()))
		));
	}

	const Margin &MarginAnimation::getFrom() const {
		return _from;
	}

	void MarginAnimation::setFrom(const Margin &from) {
		_from = from;
	}

	const Margin &MarginAnimation::getTo() const {
		return _to;
	}

	void MarginAnimation::setTo(const Margin &to) {
		_to = to;
	}
}