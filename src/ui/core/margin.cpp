#include "margin.h"

namespace ui {
	Margin Margin::zero = Margin(0);

	void Margin::setBottom(int32_t value) {
		bottom = value;
	}

	int32_t Margin::getBottom() const {
		return bottom;
	}

	void Margin::setRight(int32_t value) {
		right = value;
	}

	int32_t Margin::getRight() const {
		return right;
	}

	void Margin::setTop(int32_t value) {
		top = value;
	}

	int32_t Margin::getTop() const {
		return top;
	}

	void Margin::setLeft(int32_t value) {
		left = value;
	}

	int32_t Margin::getLeft() const {
		return left;
	}

	Margin::Margin(int32_t left, int32_t top, int32_t right, int32_t bottom) : left(left), top(top), right(right), bottom(bottom) {

	}

	Margin::Margin(int32_t horizontal, int32_t vertical) : left(horizontal), top(vertical), right(horizontal), bottom(vertical) {

	}

	Margin::Margin(int32_t uniformValue) : left(uniformValue), top(uniformValue), right(uniformValue), bottom(uniformValue) {

	}
}