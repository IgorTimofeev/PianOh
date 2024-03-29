#pragma once

#include "Arduino.h"
#include <cstdint>
#include <climits>
#include <limits>

namespace grafica {
	struct Size {
		public:
			static const uint16_t calculated = std::numeric_limits<uint16_t>::max();

			Size() = default;
			Size(const Size& size) = default;

			Size(uint16_t width, uint16_t height) :
				_width(width),
				_height(height)
			{

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

			Size interpolate(const Size &to, const double &position) const {
				return {
					(uint16_t) (getWidth() + position * (to.getWidth() - getWidth())),
					(uint16_t) (getHeight() + position * (to.getHeight() - getHeight()))
				};
			}

		private:
			uint16_t _width = 0;
			uint16_t _height = 0;
	};
}