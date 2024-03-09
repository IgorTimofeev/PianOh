#pragma once

#include "Arduino.h"
#include <cstdint>
#include "point.h"
#include "size.h"
#include "ui/event.h"

namespace ui {
	class Bounds {
		public:
			Bounds(int32_t x, int32_t y, int32_t width, int32_t height) :
				_x(x),
				_y(y),
				_width(width),
				_height(height)
			{

			}

			Bounds() : Bounds(0, 0, 0, 0) {

			}

			Bounds(const Point &position, const Size &size) : Bounds(position.getX(), position.getY(), size.getWidth(), size.getHeight()) {

			}

			explicit Bounds(const Size &size) : Bounds(Point(), size) {

			}

//			Bounds(const Bounds &bounds) = default;

			int32_t getX() const {
				return _x;
			}

			void setX(int32_t value) {
				_x = value;
			}

			int32_t getY() const {
				return _y;
			}

			void setY(int32_t value) {
				_y = value;
			}

			uint16_t getWidth() const {
				return _width;
			}

			void setWidth(uint16_t value) {
				_width = value;
			}

			uint16_t getHeight() const {
				return _height;
			}

			void setHeight(uint16_t value) {
				_height = value;
			}

			Point getPosition() const {
				return {getX(), getY()};
			}

			Point getSize() const {
				return {getWidth(), getHeight()};
			}

			bool intersectsWith(TouchEvent& event) const {
//				Serial.print("INTER ");
//				Serial.print(event.getX());
//				Serial.print(" x ");
//				Serial.print(event.getY());
//				Serial.print(" on ");
//				Serial.print(_x);
//				Serial.print(" x ");
//				Serial.print(_y);
//				Serial.print(" x ");
//				Serial.print(_width);
//				Serial.print(" x ");
//				Serial.println(_height);

				return
					event.getX() >= _x
					&& event.getY() >= _y
					&& event.getX() <= _x + _width
					&& event.getY() <= _y + _height;
			}

			void debugPrint() const {
				Serial.print("position: ");
				getPosition().debugPrint();
				Serial.print(", getChildrenCount: ");
				getSize().debugPrint();
			}

		private:
			int32_t _x = 0;
			int32_t _y = 0;
			uint16_t _width = 0;
			uint16_t _height = 0;
	};
}