#pragma once

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "FT6336U.h"

#include "size.h"
#include "point.h"
#include "bounds.h"
#include "color.h"
#include "grafica/elements/workspace.h"

namespace grafica {
	class TouchPoint {
		public:
			Point position = Point();
			bool down = false;
	};

	class Display {
		public:
			Display(int8_t sdaPin, int8_t sclPin, uint8_t rstPin, uint8_t intPin);

			virtual void clear();
			virtual Size measureText(const String& text, const uint8_t& fontSize);
			virtual void drawText(const Point& position, const Color& color, const String& text, const uint8_t& size);
			virtual void drawCircle(const Point& position, int32_t radius, const Color& color);
			virtual void drawRectangle(const Bounds& bounds, const Color& color);
			virtual void drawRectangle(const Bounds& bounds, uint16_t radius, const Color& color);
			virtual void drawFastHLine(const Point& position, uint16_t size, const Color& color);
			virtual void drawFastVLine(const Point& position, uint16_t size, const Color& color);
			virtual void drawImage(const Bounds& bounds, const uint16_t* data);
			virtual void flush();

			virtual void begin();
			virtual void render();
			virtual void readTouch();

			// -------------------------------- Getters & setters --------------------------------

			Workspace& getWorkspace();

		protected:
			virtual void onTouchDown();
			virtual void onTouchDrag();
			virtual void onTouchUp();
			virtual void onPinchDown();
			virtual void onPinchDrag();
			virtual void onPinchUp();

		private:
			static volatile bool _touchInterrupted;

			uint8_t _intPin;

			TFT_eSPI _screen = TFT_eSPI();
			TFT_eSprite _sprite = TFT_eSprite(&_screen);

			Workspace _workspace;

			bool _touched = false;
			bool _pinched = false;

			FT6336U _touchPanel;

			TouchPoint _touchPoints[2] {
				TouchPoint(),
				TouchPoint()
			};

			static void onTouchInterrupted();

			Point rotateTouchPoint(uint16_t x, uint16_t y);
			Point readPoint1();
			Point readPoint2();
	};
}
