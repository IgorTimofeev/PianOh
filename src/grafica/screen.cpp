#include <cstdint>
#include "Arduino.h"
#include "screen.h"
#include "grafica/elements/workspace.h"

namespace grafica {
	Screen::Screen(
		const Size &resolution,
		const uint8_t &tftLedPin,
		const uint8_t &touchSdaPin,
		const uint8_t &touchSclPin,
		const uint8_t &touchRstPin,
		const uint8_t &touchIntPin
	) :
		_resolution(resolution),
		_touchIntPin(touchIntPin),
		_tftLedPin(tftLedPin),
		_touchPanel(FT6336U(
			(int8_t) touchSdaPin,
			(int8_t) touchSclPin,
			touchRstPin,
			touchIntPin
		))
	{

	}

	void Screen::begin() {
		// TFT
		_tft.init();
		_tft.setRotation(1);

		_buffer.setAttribute(PSRAM_ENABLE, true);
		_buffer.setColorDepth(8);
		_buffer.createSprite((int16_t) _resolution.getWidth(), (int16_t) _resolution.getHeight());

		// Brightness

		// Touch
		_touchPanel.begin();

		pinMode(_touchIntPin, INPUT_PULLUP);
		attachInterrupt(digitalPinToInterrupt(_touchIntPin), Screen::onTouchInterrupted, CHANGE);
	}

	void Screen::tick() {
		readTouch();
	}

	void Screen::setBrightness(const uint8_t& value) const {
		// Not on ESP32 C3 :(
		// dacWrite(_brightnessPin, value);
	}

	const Size &Screen::getResolution() const {
		return _resolution;
	}

	// -------------------------------- Rendering --------------------------------

	Size Screen::measureText(const String &text) {
		return {
			(uint16_t) _buffer.textWidth(text),
			(uint16_t) _buffer.fontHeight()
		};
	}

	void Screen::setFont(const uint8_t* array) {
		_buffer.unloadFont();
		_buffer.loadFont(array);
	}

	void Screen::renderImage(const Bounds &bounds, const uint16_t *data) {
		_buffer.pushImage(
			bounds.getX(),
			bounds.getY(),
			bounds.getWidth(),
			bounds.getHeight(),
			data
		);
	}

	void Screen::renderCircle(const Point &position, int32_t radius, const Color &color) {
		_buffer.fillSmoothCircle(
			(int16_t) position.getX(),
			(int16_t) position.getY(),
			(int16_t) radius,
			_buffer.color24to16(color.toUint32())
		);
	}

	void Screen::renderText(const Point &position, const Color &color, const String &text) {
		_buffer.setTextColor(_buffer.color24to16(color.toUint32()));
		_buffer.setCursor((int16_t) position.getX(), (int16_t) position.getY());
		_buffer.print(text);
	}

	void Screen::renderRectangle(const Bounds &bounds, uint16_t radius, const Color &color) {
		_buffer.fillSmoothRoundRect(
			(int16_t) bounds.getX(),
			(int16_t) bounds.getY(),
			(int16_t) bounds.getWidth(),
			(int16_t) bounds.getHeight(),
			(int16_t) radius,
			_buffer.color24to16(color.toUint32())
		);
	}

	void Screen::renderRectangle(const Bounds &bounds, const Color &color) {
		_buffer.fillRect(
			(int16_t) bounds.getX(),
			(int16_t) bounds.getY(),
			(int16_t) bounds.getWidth(),
			(int16_t) bounds.getHeight(),
			_buffer.color24to16(color.toUint32())
		);
	}

	void Screen::clear() {
		_buffer.fillSprite(TFT_BLACK);
	}

	void Screen::flush() {
		_buffer.pushSprite(0, 0);
	}

	void Screen::renderHorizontalLine(const Point &position, uint16_t size, const Color &color) {
		_buffer.drawFastHLine(
			position.getX(),
			position.getY(),
			size,
			_buffer.color24to16(color.toUint32())
		);
	}

	void Screen::renderVerticalLine(const Point &position, uint16_t size, const Color &color) {
		_buffer.drawFastVLine(
			position.getX(),
			position.getY(),
			size,
			_buffer.color24to16(color.toUint32())
		);
	}

	// -------------------------------- Touch --------------------------------

	volatile bool Screen::_touchInterrupted = false;
	
	TouchPoint &Screen::getTouchPoint1() {
		return _touchPoints[0];
	}

	TouchPoint &Screen::getTouchPoint2() {
		return _touchPoints[1];
	}

	void Screen::onTouchInterrupted() {
		_touchInterrupted = true;
	}

	Point Screen::rotateTouchPoint(uint16_t x, uint16_t y) {
		switch (_tft.getRotation()) {
			// 270
			case 1:
				auto tmp = x;
				x = y;
				y = _resolution.getHeight() - tmp;

				break;
		}

		return {x, y};
	}

	Point Screen::readTouchPoint1() {
		return rotateTouchPoint(_touchPanel.read_touch1_x(), _touchPanel.read_touch1_y());
	}

	Point Screen::readTouchPoint2() {
		return rotateTouchPoint(_touchPanel.read_touch2_x(), _touchPanel.read_touch2_y());
	}

	void Screen::onTouchDown(const Point& point) {

	}

	void Screen::onTouchDrag(const Point& point) {

	}

	void Screen::onTouchUp(const Point& point) {

	}

	void Screen::onPinchDown(const Point& point1, const Point& point2) {

	}

	void Screen::onPinchDrag(const Point& point1, const Point& point2) {

	}

	void Screen::onPinchUp(const Point& point1, const Point& point2) {

	}

	void Screen::callOnTouchDown() {
		auto& point = _touchPoints[0].getPosition();

		onTouchDown(point);
		_onTouchDown.call(point);
	}

	void Screen::callOnTouchDrag() {
		auto& point = _touchPoints[0].getPosition();

		onTouchDrag(point);
		_onTouchDrag.call(point);
	}

	void Screen::callOnTouchUp() {
		auto& point = _touchPoints[0].getPosition();

		onTouchUp(point);
		_onTouchUp.call(point);
	}

	void Screen::callOnPinchDown() {
		auto& point1 = _touchPoints[0].getPosition();
		auto& point2 = _touchPoints[1].getPosition();

		onPinchDown(point1, point2);
		_onPinchDown.call(point1, point2);
	}

	void Screen::callOnPinchDrag() {
		auto& point1 = _touchPoints[0].getPosition();
		auto& point2 = _touchPoints[1].getPosition();

		onPinchDrag(point1, point2);
		_onPinchDrag.call(point1, point2);
	}

	void Screen::callOnPinchUp() {
		auto& point1 = _touchPoints[0].getPosition();
		auto& point2 = _touchPoints[1].getPosition();

		onPinchUp(point1, point2);
		_onPinchUp.call(point1, point2);
	}

	void Screen::readTouch() {
		if (!_touchInterrupted)
			return;

		_touchInterrupted = false;

		auto isDown1 = _touchPanel.read_touch1_event() == 2;
		auto isDown2 = _touchPanel.read_touch2_event() == 2;

		if (isDown1) {
			if (isDown2) {
				// Pinch drag
				if (_isPinched) {
					auto point1 = readTouchPoint1();
					auto point2 = readTouchPoint2();

					if (
						point1 != _touchPoints[0].getPosition()
						|| point2 != _touchPoints[1].getPosition()
					) {
						_touchPoints[0].setPosition(point1);
						_touchPoints[1].setPosition(point2);

						callOnPinchDrag();
					}
				}
				// Pinch down
				else {
					_isPinched = true;

					_touchPoints[0].setDown(true);
					_touchPoints[0].setPosition(readTouchPoint1());

					_touchPoints[1].setDown(true);
					_touchPoints[1].setPosition(readTouchPoint2());

					callOnPinchDown();
				}
			}
			else {
				// Pinch up
				if (_isPinched) {
					_isPinched = false;

					_touchPoints[1].setDown(false);
					_touchPoints[1].setPosition(readTouchPoint2());

					callOnPinchUp();
				}
				// Touch drag
				else if (_isTouched) {
					auto point1 = readTouchPoint1();

					if (point1 != _touchPoints[0].getPosition()) {
						_touchPoints[0].setPosition(point1);

						callOnTouchDrag();
					}
				}
				// Touch down
				else {
					_isTouched = true;

					_touchPoints[0].setDown(true);
					_touchPoints[0].setPosition(readTouchPoint1());

					callOnTouchDown();
				}
			}
		}
		else {
			// Pinch up
			if (_isPinched) {
				_isPinched = false;

				_touchPoints[1].setDown(false);
				_touchPoints[1].setPosition(readTouchPoint2());

				callOnPinchUp();
			}

			// Touch up
			if (_isTouched) {
				_isTouched = false;

				_touchPoints[0].setDown(false);
				_touchPoints[0].setPosition(readTouchPoint1());

				callOnTouchUp();
			}
		}
	}
}
