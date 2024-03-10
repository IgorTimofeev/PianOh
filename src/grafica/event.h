#pragma once

namespace grafica {
	enum TouchEventType: uint8_t {
		Touch,
		Drag
	};

	class TouchEvent {
		public:
			TouchEvent(TouchEventType type, uint16_t x, uint16_t y) : _type(type), _x(x), _y(y) {

			}

			TouchEventType getType() const {
				return _type;
			}

			void setType(TouchEventType value) {
				_type = value;
			}

			uint16_t getX() const {
				return _x;
			}

			void setX(uint16_t value) {
				_x = value;
			}

			uint16_t getY() const {
				return _y;
			}

			void setY(uint16_t value) {
				_y = value;
			}

		private:
			TouchEventType _type;
			uint16_t _x;
			uint16_t _y;
	};
}