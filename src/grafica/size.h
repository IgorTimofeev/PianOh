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
				width(width),
				height(height)
			{

			}

			uint16_t getWidth() const {
				return width;
			}

			void setWidth(uint16_t value) {
				width = value;
			}

			uint16_t getHeight() const {
				return height;
			}

			void setHeight(uint16_t value) {
				height = value;
			}

			void debugPrint() const {
				Serial.print(getWidth());
				Serial.print(" x ");
				Serial.print(getHeight());
			}

		private:
			uint16_t width = 0;
			uint16_t height = 0;
	};
}