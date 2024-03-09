#pragma once

#include "Arduino.h"
#include <cstdint>

namespace ui {
	struct Point {
		public:
			Point() = default;
			Point(const Point& point) = default;

			Point(int32_t x, int32_t y) : x(x), y(y) {

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

			void debugPrint() const {
				Serial.print(getX());
				Serial.print(" x ");
				Serial.print(getY());
			}

		private:
			int32_t x = 0;
			int32_t y = 0;
	};
}