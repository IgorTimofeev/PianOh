#include "animation.h"
#include "Arduino.h"
#include "grafica/elements/element.h"

namespace grafica {
	void Animation::start() {
		_start = micros();
	}

	void Animation::stop() {
		_start = 0;
	}

	bool Animation::tick(Element *element) {
		double position = (double) (micros() - _start) / (double) _duration;

		if (position > 1)
			position = 1;

		onTick(element, position);

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