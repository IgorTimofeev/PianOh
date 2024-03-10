#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/linear_gradient_view.h"

using namespace grafica;

namespace ui {
	class Piano : public Element {
		public:
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
			const uint8_t stripLedCount = 180;

			Piano() {
				setSize(Size(
					keysWidth + keysMargin.getHorizontal(),
					keysMargin.getVertical() + stripHeight + whiteKeySize.getHeight()
				));
			}

		protected:
			void render(Display &display) override {
				auto bounds = getBounds();

				// Casing
				display.drawRectangle(bounds, Color::black);

				// Controls
				Size controlsSize = Size(controlsWidth, keysMargin.getTop() - controlsMargin - controlsMargin);

				Bounds controlsBounds = Bounds(
					Point(
						bounds.getX() + bounds.getWidth() / 2 - controlsSize.getWidth() / 2,
						bounds.getY() + controlsMargin
					),
					controlsSize
				);

				// Glass
				display.drawRectangle(controlsBounds, Color::gray);

				// Screen
				auto screenBounds = Bounds(
					controlsBounds.getX() + displayMargin,
					controlsBounds.getY() + displayMargin,
					displayWidth,
					controlsSize.getHeight() - displayMargin * 2
				);

				display.drawRectangle(screenBounds, Color::white);

				// Knob
				auto knobPosition = Point(
					screenBounds.getX() + screenBounds.getWidth() + 10,
					screenBounds.getY() + screenBounds.getHeight() / 2
				);

				display.drawCircle(knobPosition, 5, Color::black);

				// Buttons
				auto buttonBounds = Bounds(
					knobPosition.getX() + 10,
					screenBounds.getY() + 3,
					6,
					3
				);

				display.drawRectangle(buttonBounds, Color::black);

				buttonBounds.setY(buttonBounds.getY() + buttonBounds.getHeight() + 3);
				display.drawRectangle(buttonBounds, Color::black);

				buttonBounds.setY(buttonBounds.getY() + buttonBounds.getHeight() + 3);
				display.drawRectangle(buttonBounds, Color::black);

				// Sl88 studio
				String sl88Text = "SL88|";
				auto sl88Size = display.measureText(sl88Text, 1);

				String studioText = "STUDIO";
				auto studioSize = display.measureText(studioText, 1);

				Point sl88Position = Point(
					bounds.getX2() - sl88Size.getWidth() - studioSize.getWidth() - 4,
					bounds.getY() + keysMargin.getTop() - sl88Size.getHeight() - 4
				);

				display.drawText(sl88Position, Color::white, sl88Text, 1);

				sl88Position.setX(sl88Position.getX() + sl88Size.getWidth());
				display.drawText(sl88Position, Color::gold, studioText, 1);

				// Strip
				auto stripBounds = Bounds(
					bounds.getX() + keysMargin.getLeft(),
					bounds.getY() + keysMargin.getTop(),
					keysWidth,
					stripHeight
				);

				drawStrip(display, stripBounds);

				// Keys
				stripBounds.setY(stripBounds.getY() + stripHeight);
				stripBounds.setHeight(whiteKeySize.getHeight());
				drawOctaves(display, stripBounds);
			}

		private:
			void drawStrip(Display &display, Bounds& bounds) const {
				display.drawRectangle(bounds, Color::gray);

				auto x = (float) bounds.getX();
				auto step = (float) bounds.getWidth() / (float) stripLedCount;

				for (uint8_t i = 0; i < stripLedCount; i++) {
					display.drawRectangle(Bounds((int32_t) x, bounds.getY(), 2, stripHeight), Color::gold);

					x += step;
				}
			}

			void drawWhiteKey(Display &display, int32_t &x, int32_t &y, uint8_t &keyIndex) {
				display.drawRectangle(
					Bounds(
						x,
						y,
						whiteKeySize.getWidth(),
						whiteKeySize.getHeight()
					),
					Color::white
				);

				x += whiteKeySize.getWidth() + whiteKeySpacing;
			}

			void drawBlackKey(Display &display, int32_t &x, int32_t &y, uint8_t &keyIndex) {
				display.drawRectangle(
					Bounds(
						x,
						y,
						blackKeySize.getWidth(),
						blackKeySize.getHeight()
					),
					Color::black
				);

				x += blackKeySize.getWidth() + blackKeySpacing;
			}

			void drawOctave(Display &display, int32_t &x, int32_t &y, uint8_t &keyIndex) {
				// White
				drawWhiteKey(display, x, y, keyIndex);
				keyIndex += 2;
				drawWhiteKey(display, x, y, keyIndex);
				keyIndex += 2;
				drawWhiteKey(display, x, y, keyIndex);
				keyIndex += 1;
				drawWhiteKey(display, x, y, keyIndex);
				keyIndex += 2;
				drawWhiteKey(display, x, y, keyIndex);
				keyIndex += 2;
				drawWhiteKey(display, x, y, keyIndex);
				keyIndex += 2;
				drawWhiteKey(display, x, y, keyIndex);
				keyIndex -= 10;
				auto oldX = x;
				x = x - (whiteKeySize.getWidth() + whiteKeySpacing) * 6 - blackKeySize.getWidth() / 2 - 1;

				// Black
				drawBlackKey(display, x, y, keyIndex);
				keyIndex += 2;
				drawBlackKey(display, x, y, keyIndex);
				keyIndex += 3;
				x += whiteKeySize.getWidth() + whiteKeySpacing;

				drawBlackKey(display, x, y, keyIndex);
				keyIndex += 2;
				drawBlackKey(display, x, y, keyIndex);
				keyIndex += 2;
				drawBlackKey(display, x, y, keyIndex);
				keyIndex += 2;
				x = oldX;
			}

			void drawOctaves(Display &display, Bounds& bounds) {
				int32_t x = bounds.getX();
				int32_t y = bounds.getY();

				uint8_t keyIndex = 0;

				// 0 octave

				// White
				drawWhiteKey(display, x, y, keyIndex);
				keyIndex += 2;
				drawWhiteKey(display, x, y, keyIndex);
				keyIndex -= 1;
				auto oldX = x;
				x = x - whiteKeySize.getWidth() - whiteKeySpacing - blackKeySize.getWidth() / 2 - 1;

				// Black
				drawBlackKey(display, x, y, keyIndex);
				keyIndex += 2;
				x = oldX;

				// 7 octaves
				for (int i = 0; i < 7; i++)
					drawOctave(display, x, y, keyIndex);

				// Last key
				drawWhiteKey(display, x, y, keyIndex);
			}
	};
}