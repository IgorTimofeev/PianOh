#pragma once

#include "Arduino.h"
#include "display.h"
#include "size.h"
#include "bounds.h"
#include "color.h"

namespace grafica {
	class TouchPoint {
		public:
			Point position = Point();
			bool down = false;
	};

	class TFTDisplay : public Display {
		public:
			TFTDisplay(int8_t sdaPin, int8_t sclPin, uint8_t rstPin, uint8_t intPin);

			void begin() override;
			void clear() override;
			void drawRectangle(const Bounds& bounds, const Color& color) override;
			void drawRectangle(const Bounds& bounds, uint16_t radius, const Color& color) override;
			void drawCircle(const Point& position, int32_t radius, const Color& color) override;
			void drawFastHLine(const Point& position, uint16_t size, const Color& color) override;
			void drawFastVLine(const Point& position, uint16_t size, const Color& color) override;
			void drawText(const Point& position, const Color& color, const String& text, const uint8_t& size) override;
			void drawImage(const Bounds& bounds, const uint16_t* data) override;
			Size measureText(const String &text, const uint8_t& fontSize) override;
			void flush() override;
			void readTouch();

		protected:
			virtual void onTouchDown();
			virtual void onTouchDrag();
			virtual void onTouchUp();
			virtual void onPinchDown();
			virtual void onPinchDrag();
			virtual void onPinchUp();

		private:
			static volatile bool _touchInterrupted;

			TFT_eSPI _display = TFT_eSPI();
			TFT_eSprite _sprite = TFT_eSprite(&_display);

			bool _touched = false;
			bool _pinched = false;

			uint8_t _intPin;
			FT6336U _touchPanel;

			TouchPoint _touchPoints[2] {
				TouchPoint(),
				TouchPoint()
			};

			static void touchInterrupt();

			const Point &rotatePoint(uint16_t x, uint16_t y);

			const Point &readPoint1();

			const Point &readPoint2();
	};
}
