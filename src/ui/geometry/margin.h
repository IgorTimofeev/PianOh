#pragma once

#include <cstdint>

namespace ui {
	struct Margin {
		public:
			static Margin zero;

			Margin() = default;

			explicit Margin(int32_t uniformValue) : left(uniformValue), top(uniformValue), right(uniformValue), bottom(uniformValue) {

			}

			Margin(int32_t horizontal, int32_t vertical) : left(horizontal), top(vertical), right(horizontal), bottom(vertical) {

			}

			Margin(int32_t left, int32_t top, int32_t right, int32_t bottom) : left(left), top(top), right(right), bottom(bottom) {

			}

			int32_t getLeft() const {
				return left;
			}

			void setLeft(int32_t value) {
				left = value;
			}

			int32_t getTop() const {
				return top;
			}

			void setTop(int32_t value) {
				top = value;
			}

			int32_t getRight() const {
				return right;
			}

			void setRight(int32_t value) {
				right = value;
			}

			int32_t getBottom() const {
				return bottom;
			}

			void setBottom(int32_t value) {
				bottom = value;
			}

		private:
			int32_t left = 0;
			int32_t top = 0;
			int32_t right = 0;
			int32_t bottom = 0;
	};

	Margin Margin::zero = Margin(0);
}