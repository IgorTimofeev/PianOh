#pragma once

#include <cstdint>
#include "point.h"
#include "size.h"

namespace ui {
	struct Bounds {
		public:
			Bounds() = default;

			Bounds(const Point &point, const Size &size) : _position(point), _size(size) {

			}

			Bounds(int32_t x, int32_t y, int32_t width, int32_t height) : Bounds(Point(x, y), Size(width, height)) {

			}

			Bounds(Size &size) : Bounds(Point(), size) {

			}

			Bounds(Bounds &bounds) : Bounds(Point(bounds.getPosition()), Size(bounds.getSize())) {

			}

			Point& getPosition() {
				return _position;
			}

			void setPosition(const Point& value) {
				_position = value;
			}

			Size& getSize() {
				return _size;
			}

			void setSize(const Size& size) {
				_size = size;
			}

			int32_t getX() {
				return getPosition().getX();
			}

			void setX(int32_t value) {
				getPosition().setX(value);
			}

			int32_t getY() {
				return getPosition().getY();
			}

			void setY(int32_t value) {
				getPosition().setY(value);
			}

			uint16_t getWidth() {
				return getSize().getWidth();
			}

			void setWidth(uint16_t value) {
				getSize().setWidth(value);
			}

			uint16_t getHeight() {
				return getSize().getHeight();
			}

			void setHeight(uint16_t value) {
				getSize().setHeight(value);
			}

		private:
			Point _position;
			Size _size;
	};
}