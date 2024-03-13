#include "piano.h"
#include "grafica/color.h"
#include "ui/application.h"

namespace ui {
	Piano::Piano() {
		setSize(Size(
			keysWidth + keysMargin.getHorizontal(),
			keysMargin.getVertical() + stripHeight + whiteKeySize.getHeight()
		));

		// Callbacks
		Application::getInstance().piano.addOnMidiRead([this](MidiEvent& event) {
			switch (event.getType()) {
				case NoteOn:
				case NoteOff:
					invalidateLayout();
					break;

				default:
					break;
			}
		});
	}

	void Piano::render(Display &display) {
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

	void Piano::drawStrip(Display &display, Bounds &bounds) const {
		display.drawRectangle(bounds, Color::gray);

		auto x = (float) bounds.getX();
		auto step = (float) bounds.getWidth() / (float) Application::getInstance().piano.getStripLength();

		for (uint16_t i = 0; i < Application::getInstance().piano.getStripLength(); i++) {
			display.drawRectangle(
				Bounds((int32_t) x, bounds.getY(), 2, stripHeight),
				Application::getInstance().piano.getStripColor(i)
			);

			x += step;
		}
	}

	void Piano::drawWhiteKey(Display &display, int32_t &x, int32_t &y, uint8_t &keyIndex) {
		display.drawRectangle(
			Bounds(
				x,
				y,
				whiteKeySize.getWidth(),
				whiteKeySize.getHeight()
			),
			Application::getInstance().piano.getKeyVelocity(keyIndex) > 0 ? Color::gold : Color::white
		);

		x += whiteKeySize.getWidth() + whiteKeySpacing;
	}

	void Piano::drawBlackKey(Display &display, int32_t &x, int32_t &y, uint8_t &keyIndex) {
		display.drawRectangle(
			Bounds(
				x,
				y,
				blackKeySize.getWidth(),
				blackKeySize.getHeight()
			),
			Application::getInstance().piano.getKeyVelocity(keyIndex) > 0 ? Color::gold : Color::black
		);

		x += blackKeySize.getWidth() + blackKeySpacing;
	}

	void Piano::drawOctave(Display &display, int32_t &x, int32_t &y, uint8_t &keyIndex) {
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

	void Piano::drawOctaves(Display &display, Bounds &bounds) {
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
}