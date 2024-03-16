#include "piano.h"
#include "grafica/color.h"
#include "ui/piano_application.h"
#include "resources/fonts.h"

using namespace devices;

namespace ui {
	Piano::Piano() {
		setSize(Size(
			keysWidth + keysMargin.getHorizontal(),
			keysMargin.getVertical() + stripHeight + whiteKeySize.getHeight()
		));

		// Callbacks
		PianoApplication::getInstance().getPiano().addOnMidiRead([this](MidiEvent& event) {
			switch (event.getType()) {
				case NoteOn:
				case NoteOff:
					invalidateRender();
					break;

				default:
					break;
			}
		});
	}

	void Piano::onRender(Screen &display) {
		auto bounds = getBounds();

		// Casing
		display.renderRectangle(bounds, Color::black);

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
		display.renderRectangle(controlsBounds, Color::gray);

		// Screen
		auto screenBounds = Bounds(
			controlsBounds.getX() + displayMargin,
			controlsBounds.getY() + displayMargin,
			displayWidth,
			controlsSize.getHeight() - displayMargin * 2
		);

		display.renderRectangle(screenBounds, Color::white);

		// Knob
		auto knobPosition = Point(
			screenBounds.getX() + screenBounds.getWidth() + 10,
			screenBounds.getY() + screenBounds.getHeight() / 2
		);

		display.renderCircle(knobPosition, 5, Color::black);

		// Buttons
		auto buttonBounds = Bounds(
			knobPosition.getX() + 10,
			screenBounds.getY() + 3,
			6,
			3
		);

		display.renderRectangle(buttonBounds, Color::black);

		buttonBounds.setY(buttonBounds.getY() + buttonBounds.getHeight() + 3);
		display.renderRectangle(buttonBounds, Color::black);

		buttonBounds.setY(buttonBounds.getY() + buttonBounds.getHeight() + 3);
		display.renderRectangle(buttonBounds, Color::black);

		// Sl88 studio
		display.setFont(resources::fonts::unscii8);

		String sl88Text = "SL88 | ";
		auto sl88Size = display.measureText(sl88Text);

		String studioText = "STUDIO";
		auto studioSize = display.measureText(studioText);

		Point sl88Position = Point(
			bounds.getX2() - sl88Size.getWidth() - studioSize.getWidth() - 4,
			bounds.getY() + keysMargin.getTop() - sl88Size.getHeight() - 4
		);

		display.renderText(sl88Position, Color::white, sl88Text);

		sl88Position.setX(sl88Position.getX() + sl88Size.getWidth());
		display.renderText(sl88Position, Color::gold, studioText);

		// Strip
		auto stripBounds = Bounds(
			bounds.getX() + keysMargin.getLeft(),
			bounds.getY() + keysMargin.getTop(),
			keysWidth,
			stripHeight
		);

		renderStrip(display, stripBounds);

		// Keys
		stripBounds.setY(stripBounds.getY() + stripHeight);
		stripBounds.setHeight(whiteKeySize.getHeight());
		renderOctaves(display, stripBounds);
	}

	void Piano::renderStrip(Screen &display, Bounds &bounds) const {
		display.renderRectangle(bounds, Color::black);

		auto step = (float) bounds.getWidth() / (float) PianoApplication::getInstance().getPiano().getStripLength();
		auto x = (float) bounds.getX() + step / 2;

		for (uint16_t i = 0; i < PianoApplication::getInstance().getPiano().getStripLength(); i++) {
			display.renderRectangle(
				Bounds((int32_t) x, bounds.getY(), 2, stripHeight),
				getEffect()
				? getEffect()->getSampleColor(PianoApplication::getInstance().getPiano(), i)
				: Color::gray
			);

			x += step;
		}
	}

	void Piano::renderWhiteKey(Screen &display, int32_t &x, int32_t &y, uint8_t &keyIndex) {
		display.renderRectangle(
			Bounds(
				x,
				y,
				whiteKeySize.getWidth(),
				whiteKeySize.getHeight()
			),
			PianoApplication::getInstance().getPiano().getKeyVelocity(keyIndex) > 0 ? Color::gold : Color::white
		);

		x += whiteKeySize.getWidth() + whiteKeySpacing;
	}

	void Piano::renderBlackKey(Screen &display, int32_t &x, int32_t &y, uint8_t &keyIndex) {
		display.renderRectangle(
			Bounds(
				x,
				y,
				blackKeySize.getWidth(),
				blackKeySize.getHeight()
			),
			PianoApplication::getInstance().getPiano().getKeyVelocity(keyIndex) > 0 ? Color::gold : Color::black
		);

		x += blackKeySize.getWidth() + blackKeySpacing;
	}

	void Piano::renderOctave(Screen &display, int32_t &x, int32_t &y, uint8_t &keyIndex) {
		// White
		renderWhiteKey(display, x, y, keyIndex);
		keyIndex += 2;
		renderWhiteKey(display, x, y, keyIndex);
		keyIndex += 2;
		renderWhiteKey(display, x, y, keyIndex);
		keyIndex += 1;
		renderWhiteKey(display, x, y, keyIndex);
		keyIndex += 2;
		renderWhiteKey(display, x, y, keyIndex);
		keyIndex += 2;
		renderWhiteKey(display, x, y, keyIndex);
		keyIndex += 2;
		renderWhiteKey(display, x, y, keyIndex);
		keyIndex -= 10;
		auto oldX = x;
		x = x - (whiteKeySize.getWidth() + whiteKeySpacing) * 6 - blackKeySize.getWidth() / 2 - 1;

		// Black
		renderBlackKey(display, x, y, keyIndex);
		keyIndex += 2;
		renderBlackKey(display, x, y, keyIndex);
		keyIndex += 3;
		x += whiteKeySize.getWidth() + whiteKeySpacing;

		renderBlackKey(display, x, y, keyIndex);
		keyIndex += 2;
		renderBlackKey(display, x, y, keyIndex);
		keyIndex += 2;
		renderBlackKey(display, x, y, keyIndex);
		keyIndex += 2;
		x = oldX;
	}

	void Piano::renderOctaves(Screen &display, Bounds &bounds) {
		int32_t x = bounds.getX();
		int32_t y = bounds.getY();

		uint8_t keyIndex = 0;

		// 0 octave

		// White
		renderWhiteKey(display, x, y, keyIndex);
		keyIndex += 2;
		renderWhiteKey(display, x, y, keyIndex);
		keyIndex -= 1;
		auto oldX = x;
		x = x - whiteKeySize.getWidth() - whiteKeySpacing - blackKeySize.getWidth() / 2 - 1;

		// Black
		renderBlackKey(display, x, y, keyIndex);
		keyIndex += 2;
		x = oldX;

		// 7 octaves
		for (int i = 0; i < 7; i++)
			renderOctave(display, x, y, keyIndex);

		// Last key
		renderWhiteKey(display, x, y, keyIndex);
	}

	Effect *Piano::getEffect() const {
		return _effect;
	}

	void Piano::setEffect(Effect *effect) {
		_effect = effect;
	}
}