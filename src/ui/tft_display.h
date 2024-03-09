#pragma once

#include "Arduino.h"
#include "display.h"
#include "size.h"
#include "bounds.h"
#include "color.h"

namespace ui {
	class TFTDisplay : public Display {
		public:
			TFTDisplay();

			void begin() override;

			void clear() override;

			void drawRectangle(const Bounds& bounds, const Color& color) override;

			void drawRectangle(const Bounds& bounds, uint16_t radius, const Color& color) override;

			void drawCircle(const Point& position, int32_t radius, const Color& color) override;

			void drawText(const Point& position, const Color& color, const String& text, const uint8_t& size) override;

			void drawImage(const Bounds& bounds, const uint16_t* data) override;

			Size measureText(const String &text) override;

			void flush() override;

			void readTouch();

		private:
			FT6336U _touch = FT6336U(
				4,
				5,
				9,
				8
			);

			TFT_eSPI _display = TFT_eSPI();
			TFT_eSprite _sprite = TFT_eSprite(&_display);
	};
}
