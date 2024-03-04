#pragma once

#include "TFT_eSPI.h"
#include "FT6336U.h"

#include "color.h"

namespace ui {
	class Workspace;

	class Display {
		public:
			virtual void clear() = 0;

			virtual void render() {
				clear();

				workspace.measure(*this);
				workspace.arrange();
				workspace.render(*this);
			}

			virtual void update() = 0;
			virtual void begin() = 0;
			virtual void drawText(const Point& position, const Color& color, const String& text) = 0;
			virtual void drawCircle(const Point& position, int32_t radius, const Color& color) = 0;
			virtual void drawRectangle(const Bounds& bounds, const Color& color) = 0;
			virtual void drawRectangle(const Bounds& bounds, uint16_t radius, const Color& color) = 0;

			virtual Bounds measureText(const String& text) = 0;

			// -------------------------------- Getters & setters --------------------------------

			const Size& getSize() {
				return workspace.getSize();
			}

			Workspace& getWorkspace() {
				return workspace;
			}

		private:
			Workspace workspace;
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

			Bounds measureText(const String &text) override {
				return {0, 0, sprite.textWidth(text), sprite.fontHeight() };
			}

		private:


	};
}
