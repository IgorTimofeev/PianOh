#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "gradient_selector.h"
#include "Adafruit_NeoPixel.h"
#include "devices/piano/effects/effect.h"

using namespace grafica;
using namespace devices;

namespace ui {
	class Piano : public Element {
		public:
			Piano();

			const uint8_t controlsWidth = 62;
			const uint8_t controlsMargin = 7;
			const uint8_t displayMargin = 4;
			const uint8_t displayWidth = 28;

			const Size whiteKeySize = Size(7, 52);
			const Size blackKeySize = Size(5, 30);
			const uint8_t whiteKeySpacing = 1;
			const uint8_t blackKeySpacing = 3;
			const Margin keysMargin = Margin(3, 42, 3, 3);
			const uint16_t keysWidth = (whiteKeySize.getWidth() + whiteKeySpacing) * 52 - whiteKeySpacing;

			const uint8_t stripHeight = 3;

			Effect *getEffect() const;

			void setEffect(Effect *effect);

		protected:
			void onRender(Screen &display) override;

		private:


			Effect* _effect = nullptr;

			void renderStrip(Screen &display, Bounds& bounds) const;
			void renderWhiteKey(Screen &display, int32_t &x, int32_t &y, uint8_t &keyIndex);
			void renderBlackKey(Screen &display, int32_t &x, int32_t &y, uint8_t &keyIndex);
			void renderOctave(Screen &display, int32_t &x, int32_t &y, uint8_t &keyIndex);
			void renderOctaves(Screen &display, Bounds& bounds);
	};
}