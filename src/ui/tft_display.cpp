#include "Arduino.h"
#include "ui/elements/workspace.h"
#include "tft_display.h"

namespace ui {
	TFTDisplay::TFTDisplay() {
		getWorkspace().setSize(Size(TFT_HEIGHT, TFT_WIDTH));
	}

	Size TFTDisplay::measureText(const String &text) {
		return {
			(uint16_t) _sprite.textWidth(text),
			(uint16_t) _sprite.fontHeight()
		};
	}

	void TFTDisplay::drawImage(const Bounds &bounds, const uint16_t *data) {
		_sprite.pushImage(
			bounds.getX(),
			bounds.getY(),
			bounds.getWidth(),
			bounds.getHeight(),
			data
		);
	}

	void TFTDisplay::begin() {
		// Display
		_display.init();
		_display.setRotation(1);

		_sprite.setColorDepth(8);
		_sprite.createSprite(TFT_HEIGHT, TFT_WIDTH);

		// Touch
		_touch.begin();
	}

	void TFTDisplay::drawCircle(const Point &position, int32_t radius, const Color &color) {
		_sprite.fillCircle(
			(int16_t) position.getX(),
			(int16_t) position.getY(),
			(int16_t) radius,
			_sprite.color24to16(color.toUint32())
		);
	}

	void TFTDisplay::drawText(const Point &position, const Color &color, const String &text, const uint8_t &size) {
		_sprite.setTextColor(_sprite.color24to16(color.toUint32()));
		_sprite.setCursor((int16_t) position.getX(), (int16_t) position.getY());
		_sprite.setTextSize(size);
		_sprite.print(text);
	}

	void TFTDisplay::drawRectangle(const Bounds &bounds, uint16_t radius, const Color &color) {
		_sprite.fillRoundRect(
			(int16_t) bounds.getX(),
			(int16_t) bounds.getY(),
			(int16_t) bounds.getWidth(),
			(int16_t) bounds.getHeight(),
			(int16_t) radius,
			_sprite.color24to16(color.toUint32())
		);
	}

	void TFTDisplay::drawRectangle(const Bounds &bounds, const Color &color) {
		_sprite.fillRect(
			(int16_t) bounds.getX(),
			(int16_t) bounds.getY(),
			(int16_t) bounds.getWidth(),
			(int16_t) bounds.getHeight(),
			_sprite.color24to16(color.toUint32())
		);
	}

	void TFTDisplay::clear() {
		_sprite.fillSprite(TFT_BLACK);
	}


	void TFTDisplay::flush() {
		_sprite.pushSprite(0, 0);
	}

	void TFTDisplay::readTouch() {
		auto points = _touch.scan();

		for (size_t i = 0; i < points.touch_count; i++) {
			auto point = points.tp[i];

			auto x = point.x;
			auto y = point.y;

			switch (_display.getRotation()) {
				// 270
				case 1:
					auto tmp = x;
					x = y;
					y = TFT_WIDTH - tmp;

					break;
			}

			auto event = TouchEvent(
				point.status == TouchStatusEnum::touch
				? TouchEventType::Touch
				: TouchEventType::Drag,
				x,
				y
			);

			getWorkspace().handleEvent(event);
		}
	}

}
