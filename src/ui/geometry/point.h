#pragma once

#include <cstdint>

namespace ui {
	struct Point {
		public:
			Point() = default;

			Point(int32_t x, int32_t y) :
				x(x),
				y(y)
			{

			}

			int32_t getX() const {
				return x;
			}

			void setX(int32_t value) {
				x = value;
			}

			int32_t getY() const {
				return y;
			}

			void setY(int32_t value) {
				y = value;
			}

		private:
			int32_t x = 0;
			int32_t y = 0;
	};
}