#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/linear_gradient_view.h"
#include "Adafruit_NeoPixel.h"
#include "devices/piano/effects/effect.h"

using namespace grafica;

namespace ui {
	class Piano : public Element {
		public:
			Piano();


		protected:
			void render(Display &display) override;

		private:
			const uint8_t controlsWidth = 62;
			const uint8_t controlsMargin = 7;
			const uint8_t displayMargin = 4;
			const uint8_t displayWidth = 28;

			const Size whiteKeySize = Size(6, 52);
			const Size blackKeySize = Size(4, 30);
			const uint8_t whiteKeySpacing = 1;
			const uint8_t blackKeySpacing = 3;
			const Margin keysMargin = Margin(3, 42, 3, 3);
			const uint16_t keysWidth = (whiteKeySize.getWidth() + whiteKeySpacing) * 52 - whiteKeySpacing;

			const uint8_t stripHeight = 3;

			void drawStrip(Display &display, Bounds& bounds) const;
			void drawWhiteKey(Display &display, int32_t &x, int32_t &y, uint8_t &keyIndex);
			void drawBlackKey(Display &display, int32_t &x, int32_t &y, uint8_t &keyIndex);
			void drawOctave(Display &display, int32_t &x, int32_t &y, uint8_t &keyIndex);
			void drawOctaves(Display &display, Bounds& bounds);
	};
}