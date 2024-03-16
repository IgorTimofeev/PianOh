#pragma once

#include <cstdint>
#include "point.h"

namespace grafica {
	class TouchPoint {
		public:
			const Point &getPosition() const;

			void setPosition(const Point &position);

			bool isDown() const;

			void setDown(bool isDown);

		private:
			Point _position = Point();
			bool _isDown = false;
	};
}
