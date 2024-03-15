#include "Arduino.h"
#include "display.h"
#include "grafica/elements/workspace.h"

namespace grafica {
	Display::Display(int8_t sdaPin, int8_t sclPin, uint8_t rstPin, uint8_t intPin, uint8_t brightnessPin) :
		_intPin(intPin),
		_brightnessPin(brightnessPin),
		_touchPanel(FT6336U(
			sdaPin,
			sclPin,
			rstPin,
			intPin
		))
	{
		
	}

	void Display::begin() {
		// Display
		_screen.init();
		_screen.setRotation(1);

		_sprite.setAttribute(PSRAM_ENABLE, true);
		_sprite.setColorDepth(8);
		_sprite.createSprite(TFT_HEIGHT, TFT_WIDTH);

		// Brightness

		// Touch
		_touchPanel.begin();

		pinMode(_intPin, INPUT_PULLUP);
		attachInterrupt(digitalPinToInterrupt(_intPin), Display::onTouchInterrupted, CHANGE);

		// Workspace
		_workspace.setSize(Size(TFT_HEIGHT, TFT_WIDTH));
	}

	void Display::tick() {
		readTouch();

		_workspace.tick();
	}

	void Display::render() {
		_workspace.measure(*this);
		_workspace.arrange();
		_workspace.render(*this);
	}

	void Display::setBrightness(const uint8_t& value) const {
		// Not on ESP32 C3 :(
		// dacWrite(_brightnessPin, value);
	}

	Workspace &Display::getWorkspace() {
		return _workspace;
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

	Point Display::readTouchPoint1() {
		return rotateTouchPoint(_touchPanel.read_touch1_x(), _touchPanel.read_touch1_y());
	}

	Point Display::readTouchPoint2() {
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
				if (_touchPinched) {
					auto point1 = readTouchPoint1();
					auto point2 = readTouchPoint2();

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
					_touchPinched = true;

					_touchPoints[0].down = true;
					_touchPoints[0].position = readTouchPoint1();

					_touchPoints[1].down = true;
					_touchPoints[1].position = readTouchPoint2();

					onPinchDown();
				}
			}
				// Down / drag / pinch up
			else {
				// Pinch up
				if (_touchPinched) {
					_touchPinched = false;

					_touchPoints[1].down = false;
					_touchPoints[1].position = readTouchPoint2();

					onPinchUp();
				}
					// Drag
				else if (_touchDown) {
					auto point1 = readTouchPoint1();

					if (point1 != _touchPoints[0].position) {
						_touchPoints[0].position = point1;

						onTouchDrag();
					}
				}
					// Down
				else {
					_touchDown = true;

					_touchPoints[0].down = true;
					_touchPoints[0].position = readTouchPoint1();

					onTouchDown();
				}
			}
		}
			// Up / pinch up
		else {
			if (_touchPinched) {
				_touchPinched = false;

				_touchPoints[1].down = false;
				_touchPoints[1].position = readTouchPoint2();

				onPinchUp();
			}

			if (_touchDown) {
				_touchDown = false;

				_touchPoints[0].down = false;
				_touchPoints[0].position = readTouchPoint1();

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
		_workspace.handleEvent(event);
	}

	void Display::onTouchDrag() {
//		Serial.print("Drag ");
//		Serial.print(_touchPoints[0].position.getX());
//		Serial.print("x");
//		Serial.print(_touchPoints[0].position.getY());
//		Serial.println();

		auto event = TouchDragEvent(_touchPoints[0].position);
		_workspace.handleEvent(event);
	}

	void Display::onTouchUp() {
//		Serial.print("Up ");
//		Serial.print(_touchPoints[0].position.getX());
//		Serial.print("x");
//		Serial.print(_touchPoints[0].position.getY());
//		Serial.println();

		auto event = TouchUpEvent(_touchPoints[0].position);
		_workspace.handleEvent(event);
	}

	void Display::onPinchDown() {
		auto event = PinchDownEvent(_touchPoints[0].position, _touchPoints[1].position);
		_workspace.handleEvent(event);
	}

	void Display::onPinchDrag() {
		auto event = PinchDragEvent(_touchPoints[0].position, _touchPoints[1].position);
		_workspace.handleEvent(event);
	}

	void Display::onPinchUp() {
		auto event = PinchUpEvent(_touchPoints[0].position, _touchPoints[1].position);
		_workspace.handleEvent(event);
	}
}
