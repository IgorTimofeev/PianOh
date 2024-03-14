#include "animation.h"
#include "Arduino.h"
#include "grafica/elements/element.h"
#include "grafica/number.h"

namespace grafica {
	void Animation::start() {
		_start = millis();
	}

	void Animation::stop() {
		_start = 0;
	}

	bool Animation::tick(Element *element, uint32_t time) {
		double position = Number::clampDouble((double) (time - _start) / (double) _duration);

		onTick(element, position);
		element->invalidateLayout();

		if (position < 1) {
			return false;
		}
		else {
			stop();

			_onCompleted.invoke();

			return true;
		}
	}

	uint32_t Animation::getDuration() const {
		return _duration;
	}

	void Animation::setDuration(uint32_t duration) {
		_duration = duration;
	}

	bool Animation::isStarted() {
		return _start > 0;
	}

	void Animation::addOnCompleted(const std::function<void()> &value) {
		_onCompleted.add(value);
	}
}