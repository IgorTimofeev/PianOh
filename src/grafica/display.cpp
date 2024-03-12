#include "display.h"
#include "grafica/elements/workspace.h"

namespace grafica {
	Display::Display(int8_t sdaPin, int8_t sclPin, uint8_t rstPin, uint8_t intPin) :
		_intPin(intPin),
		_touchPanel(FT6336U(
			sdaPin,
			sclPin,
			rstPin,
			intPin
		))
	{
		getWorkspace().setSize(Size(TFT_HEIGHT, TFT_WIDTH));
	}

	Workspace &Display::getWorkspace() {
		return _workspace;
	}

	void Display::render() {
		_workspace.measure(*this);
		_workspace.arrange();
		_workspace.render(*this);
	}

	void Display::begin() {
		// Display
		_screen.init();
		_screen.setRotation(1);

		_sprite.setColorDepth(8);
		_sprite.createSprite(TFT_HEIGHT, TFT_WIDTH);

		// Touch
		_touchPanel.begin();

		pinMode (_intPin, INPUT_PULLUP);
		attachInterrupt(digitalPinToInterrupt(_intPin), Display::onTouchInterrupted, CHANGE);
	}

	// ------------------------------------------- Rendering -------------------------------------------

	Size Display::measureText(const String &text, const uint8_t& fontSize) {
		_sprite.setTextSize(fontSize);

		return {
			(uint16_t) _sprite.textWidth(text),
			(uint16_t) _sprite.fontHeight()
		};
	}

	void Display::drawImage(const Bounds &bounds, const uint16_t *data) {
		_sprite.pushImage(
			bounds.getX(),
			bounds.getY(),
			bounds.getWidth(),
			bounds.getHeight(),
			data
		);
	}

	void Display::drawCircle(const Point &position, int32_t radius, const Color &color) {
		_sprite.fillCircle(
			(int16_t) position.getX(),
			(int16_t) position.getY(),
			(int16_t) radius,
			_sprite.color24to16(color.toUint32())
		);
	}

	void Display::drawText(const Point &position, const Color &color, const String &text, const uint8_t &size) {
		_sprite.setTextColor(_sprite.color24to16(color.toUint32()));
		_sprite.setCursor((int16_t) position.getX(), (int16_t) position.getY());
		_sprite.setTextSize(size);
		_sprite.print(text);
	}

	void Display::drawRectangle(const Bounds &bounds, uint16_t radius, const Color &color) {
		_sprite.fillRoundRect(
			(int16_t) bounds.getX(),
			(int16_t) bounds.getY(),
			(int16_t) bounds.getWidth(),
			(int16_t) bounds.getHeight(),
			(int16_t) radius,
			_sprite.color24to16(color.toUint32())
		);
	}

	void Display::drawRectangle(const Bounds &bounds, const Color &color) {
		_sprite.fillRect(
			(int16_t) bounds.getX(),
			(int16_t) bounds.getY(),
			(int16_t) bounds.getWidth(),
			(int16_t) bounds.getHeight(),
			_sprite.color24to16(color.toUint32())
		);
	}

	void Display::clear() {
		_sprite.fillSprite(TFT_BLACK);
	}


	void Display::flush() {
		_sprite.pushSprite(0, 0);
	}

	void Display::drawFastHLine(const Point &position, uint16_t size, const Color &color) {
		_sprite.drawFastHLine(
			position.getX(),
			position.getY(),
			size,
			_sprite.color24to16(color.toUint32())
		);
	}

	void Display::drawFastVLine(const Point &position, uint16_t size, const Color &color) {
		_sprite.drawFastVLine(
			position.getX(),
			position.getY(),
			size,
			_sprite.color24to16(color.toUint32())
		);
	}

	// ------------------------------------------- Touch -------------------------------------------

	volatile bool Display::_touchInterrupted = false;

	void Display::onTouchInterrupted() {
		_touchInterrupted = true;
	}

	Point Display::rotateTouchPoint(uint16_t x, uint16_t y) {
		switch (_screen.getRotation()) {
			// 270
			case 1:
				auto tmp = x;
				x = y;
				y = TFT_WIDTH - tmp;

				break;
		}

		return {x, y};
	}

	Point Display::readPoint1() {
		return rotateTouchPoint(_touchPanel.read_touch1_x(), _touchPanel.read_touch1_y());
	}

	Point Display::readPoint2() {
		return rotateTouchPoint(_touchPanel.read_touch2_x(), _touchPanel.read_touch2_y());
	}

	void Display::readTouch() {
		if (!_touchInterrupted)
			return;

		_touchInterrupted = false;

		auto isDown1 = _touchPanel.read_touch1_event() == 2;
		auto isDown2 = _touchPanel.read_touch2_event() == 2;

		// Down / drag / pinch
		if (isDown1) {
			// Pinch
			if (isDown2) {
				// Pinch drag
				if (_pinched) {
					auto point1 = readPoint1();
					auto point2 = readPoint2();

					if (
						point1 != _touchPoints[0].position
						|| point2 != _touchPoints[1].position
						) {
						_touchPoints[0].position = point1;
						_touchPoints[1].position = point2;

						onPinchDrag();
					}
				}
					// Pinch down
				else {
					_pinched = true;

					_touchPoints[0].down = true;
					_touchPoints[0].position = readPoint1();

					_touchPoints[1].down = true;
					_touchPoints[1].position = readPoint2();

					onPinchDown();
				}
			}
				// Down / drag / pinch up
			else {
				// Pinch up
				if (_pinched) {
					_pinched = false;

					_touchPoints[1].down = false;
					_touchPoints[1].position = readPoint2();

					onPinchUp();
				}
					// Drag
				else if (_touched) {
					auto point1 = readPoint1();

					if (point1 != _touchPoints[0].position) {
						_touchPoints[0].position = point1;

						onTouchDrag();
					}
				}
					// Down
				else {
					_touched = true;

					_touchPoints[0].down = true;
					_touchPoints[0].position = readPoint1();

					onTouchDown();
				}
			}
		}
			// Up / pinch up
		else {
			if (_pinched) {
				_pinched = false;

				_touchPoints[1].down = false;
				_touchPoints[1].position = readPoint2();

				onPinchUp();
			}

			if (_touched) {
				_touched = false;

				_touchPoints[0].down = false;
				_touchPoints[0].position = readPoint1();

				onTouchUp();
			}
		}
	}

	void Display::onTouchDown() {
//		Serial.print("Down ");
//		Serial.print(_touchPoints[0].position.getX());
//		Serial.print("x");
//		Serial.print(_touchPoints[0].position.getY());
//		Serial.println();

		auto event = TouchDownEvent(_touchPoints[0].position);
		getWorkspace().handleEvent(event);
	}

	void Display::onTouchDrag() {
//		Serial.print("Drag ");
//		Serial.print(_touchPoints[0].position.getX());
//		Serial.print("x");
//		Serial.print(_touchPoints[0].position.getY());
//		Serial.println();

		auto event = TouchDragEvent(_touchPoints[0].position);
		getWorkspace().handleEvent(event);
	}

	void Display::onTouchUp() {
//		Serial.print("Up ");
//		Serial.print(_touchPoints[0].position.getX());
//		Serial.print("x");
//		Serial.print(_touchPoints[0].position.getY());
//		Serial.println();

		auto event = TouchUpEvent(_touchPoints[0].position);
		getWorkspace().handleEvent(event);
	}

	void Display::onPinchDown() {
		auto event = PinchDownEvent(_touchPoints[0].position, _touchPoints[1].position);
		getWorkspace().handleEvent(event);
	}

	void Display::onPinchDrag() {
		auto event = PinchDragEvent(_touchPoints[0].position, _touchPoints[1].position);
		getWorkspace().handleEvent(event);
	}

	void Display::onPinchUp() {
		auto event = PinchUpEvent(_touchPoints[0].position, _touchPoints[1].position);
		getWorkspace().handleEvent(event);
	}
}
