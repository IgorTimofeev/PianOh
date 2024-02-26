#pragma once

#include <cstdint>
#include "point.h"
#include "size.h"

namespace ui {
	struct Rectangle {
		public:
			Rectangle() = default;

			Rectangle(const Point &point, const Size &size) : point(point), size(size) {

			}

			explicit Rectangle(const Size &size) : Rectangle(Point(), size) {

			}

			Rectangle(int32_t x, int32_t y, int32_t width, int32_t height) : Rectangle(Point(x, y), Size(width, height)) {

			}

			Point point;
			Size size;
	};
}