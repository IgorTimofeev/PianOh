#include "Arduino.h"
#include "margin_animation.h"
#include "grafica/elements/element.h"

namespace grafica {
	MarginAnimation::MarginAnimation() = default;

	Margin MarginAnimation::interpolate(const double &position) {
		auto from = getFrom();
		auto to = getTo();

		return {
			(int32_t) (from.getLeft() + position * (to.getLeft() - from.getLeft())),
			(int32_t) (from.getTop() + position * (to.getTop() - from.getTop())),
			(int32_t) (from.getRight() + position * (to.getRight() - from.getRight())),
			(int32_t) (from.getBottom() + position * (to.getBottom() - from.getBottom()))
		};
	}

	MarginAnimation::MarginAnimation(const Margin &from, const Margin &to, const uint32_t &duration) : Animation(from, to, duration) {}
}