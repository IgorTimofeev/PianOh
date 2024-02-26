#pragma once

#include <cstdint>
#include "point.h"
#include "size.h"

namespace ui {
	struct Bounds {
		public:
			Bounds() = default;

			Bounds(const Point &point, const Size &size) : point(point), size(size) {

			}

			explicit Bounds(const Size &size) : Bounds(Point(), size) {

			}

			Bounds(int32_t x, int32_t y, int32_t width, int32_t height) : Bounds(Point(x, y), Size(width, height)) {

			}

			Point point;
			Size size;
	};
}