#include "animation.h"
#include "Arduino.h"
#include "grafica/elements/element.h"

namespace grafica {
	template<typename T>
	void Animation<T>::start() {
		_start = micros();
	}

	template<typename T>
	void Animation<T>::stop() {
		_start = 0;
	}

	template<typename T>
	bool Animation<T>::tick() {
		double position = (double) (micros() - _start) / (double) _duration;

		if (position > 1)
			position = 1;

		_onTick.invoke(position);

		if (position < 1) {
			return true;
		}
		else {
			_onCompleted.invoke();

			return false;
		}
	}

	template<typename T>
	bool Animation<T>::isStarted() const {
		return _start > 0;
	}

	template<typename T>
	void Animation<T>::addOnCompleted(const std::function<void()> &value) {
		_onCompleted.add(value);
	}

	template<typename T>
	T Animation<T>::getFrom() const {
		return _from;
	}

	template<typename T>
	void Animation<T>::setFrom(T from) {
		_from = from;
	}

	template<typename T>
	T Animation<T>::getTo() const {
		return _to;
	}

	template<typename T>
	void Animation<T>::setTo(T to) {
		_to = to;
	}

	template<typename T>
	uint32_t Animation<T>::getDuration() const {
		return _duration;
	}

	template<typename T>
	void Animation<T>::setDuration(const uint32_t &duration) {
		_duration = duration;
	}

}