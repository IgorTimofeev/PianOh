#pragma once

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "FT6336U.h"

#include "color.h"

namespace ui {
	class Workspace;

	class Display {
		public:
			Display() {
				setFramerate(30);
			}

			virtual void clear() = 0;

			virtual void render() {
//				if (micros() <= _renderDeadline)
//					return;

				clear();

				_workspace.measure(*this);
				_workspace.arrange();
				_workspace.render(*this);

//				_renderDeadline = micros() + _renderInterval;
			}

			virtual void update() = 0;
			virtual void begin() = 0;
			virtual void drawText(const Point& position, const Color& color, const String& text) = 0;
			virtual void drawCircle(const Point& position, int32_t radius, const Color& color) = 0;
			virtual void drawRectangle(const Bounds& bounds, const Color& color) = 0;
			virtual void drawRectangle(const Bounds& bounds, uint16_t radius, const Color& color) = 0;

			virtual Size measureText(const String& text) = 0;

			// -------------------------------- Getters & setters --------------------------------

			void setFramerate(uint8_t value) {
				_renderInterval = 1000000 / value;
			}

			uint8_t getFramerate(uint8_t value) const {
				return 1000000 / _renderInterval;
			}

			Workspace& getWorkspace() {
				return _workspace;
			}

		private:
			uint32_t _renderDeadline = 0;
			uint32_t _renderInterval = 0;
			Workspace _workspace;
	};

	class TFTDisplay : public Display {
		public:
			FT6336U touch = FT6336U(
				4,
				5,
				9,
				8
			);

			TFT_eSPI display = TFT_eSPI();
			TFT_eSprite sprite = TFT_eSprite(&display);

			TFTDisplay() {
				getWorkspace().setSize(Size(TFT_HEIGHT, TFT_WIDTH));
			}

			void begin() override {
				// Display
				display.init();
				display.setRotation(1);

				sprite.setColorDepth(8);
				sprite.createSprite(TFT_HEIGHT, TFT_WIDTH);
				sprite.setTextColor(TFT_WHITE);
				sprite.setTextSize(2);

				// Touch
				touch.begin();
			}

			void update() override {
				sprite.pushSprite(0, 0);
			}

			void clear() override {
				sprite.fillSprite(TFT_BLACK);
			}

			void drawRectangle(const Bounds& bounds, const Color& color) override {
				sprite.fillRect(
					(int16_t) bounds.getX(),
					(int16_t) bounds.getY(),
					(int16_t) bounds.getWidth(),
					(int16_t) bounds.getHeight(),
					color.toUint32()
				);
			}

			void drawRectangle(const Bounds& bounds, uint16_t radius, const Color& color) override {
				sprite.fillRoundRect(
					(int16_t) bounds.getX(),
					(int16_t) bounds.getY(),
					(int16_t) bounds.getWidth(),
					(int16_t) bounds.getHeight(),
					(int16_t) radius,
					sprite.color24to16(color.toUint32())
				);
			}

			void drawCircle(const Point& position, int32_t radius, const Color& color) override {
				sprite.fillCircle(
					(int16_t) position.getX(),
					(int16_t) position.getY(),
					(int16_t) radius,
					sprite.color24to16(color.toUint32())
				);
			}

			void drawText(const Point& position, const Color& color, const String& text) override {
				sprite.setTextColor(sprite.color24to16(color.toUint32()));
				sprite.setCursor((int16_t) position.getX(), (int16_t) position.getY());
				sprite.print(text);
			}

			Size measureText(const String &text) override {
				return {
					(uint16_t) sprite.textWidth(text),
					(uint16_t) sprite.fontHeight()
				};
			}

			void readTouch() {
				auto points = touch.scan();

				for (size_t i = 0; i < points.touch_count; i++) {
					auto point = points.tp[i];

					auto x = point.x;
					auto y = point.y;

					switch (display.getRotation()) {
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

		private:


	};
}
