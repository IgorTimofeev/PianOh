#include "Arduino.h"
#include "size_animation.h"
#include "grafica/elements/element.h"

namespace grafica {
	SizeAnimation::SizeAnimation() = default;

	SizeAnimation::SizeAnimation(const Size &from, const Size &to, const uint32_t &duration) : Animation(from, to, duration) {}

	Size SizeAnimation::interpolate(const double &position) {
		auto from = getFrom();
		auto to = getTo();

		return {
			(uint16_t) (from.getWidth() + position * (to.getWidth() - from.getWidth())),
			(uint16_t) (from.getHeight() + position * (to.getHeight() - from.getHeight()))
		};
	}
}