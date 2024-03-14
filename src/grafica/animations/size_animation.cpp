#include "Arduino.h"
#include "size_animation.h"
#include "grafica/elements/element.h"

namespace grafica {
	SizeAnimation::SizeAnimation(const Size &from, const Size &to, uint32_t duration) {
		setFrom(from);
		setTo(to);
		setDuration(duration);
	}

	void SizeAnimation::onTick(Element *element, double position) {
		element->setSize(Size(
			(uint16_t) (_from.getWidth() + position * (_to.getWidth() - _from.getWidth())),
			(uint16_t) (_from.getHeight() + position * (_to.getHeight() - _from.getHeight()))
		));
	}

	const Size &SizeAnimation::getFrom() const {
		return _from;
	}

	void SizeAnimation::setFrom(const Size &from) {
		_from = from;
	}

	const Size &SizeAnimation::getTo() const {
		return _to;
	}

	void SizeAnimation::setTo(const Size &to) {
		_to = to;
	}
}