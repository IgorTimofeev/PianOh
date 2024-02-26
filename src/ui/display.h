#pragma once

#include "color.h"

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SSD1306_EXTERNALVCC 0x01  ///< External display voltage source
#define SSD1306_SWITCHCAPVCC 0x02 ///< Gen. display voltage from 3.3V

namespace ui {
	class Workspace;

	class Display {
		public:
			virtual void clear() = 0;
			virtual void show() = 0;

			virtual void render() {
				clear();

				workspace.measure();
				workspace.arrange();
				workspace.render(*this);

				show();
			}

			virtual void begin() = 0;
			virtual void drawText(Point& position, const Color& color, const String& text) = 0;
			virtual void drawRectangle(Bounds& bounds, const Color& color) = 0;

			// -------------------------------- Getters & setters --------------------------------

			const Size& getSize() {
				return workspace.getSize();
			}

			Workspace& getWorkspace() {
				return workspace;
			}

		private:
			Workspace workspace = Workspace();
	};

	class SSD1306Display : public Display {
		public:
			explicit SSD1306Display(const Adafruit_SSD1306& adafruit) : _adafruit(adafruit) {
				getWorkspace().setSize(Size(_adafruit.width(), _adafruit.height()));
			}

			void begin() override {
				_adafruit.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
			}

			void clear() override {
				_adafruit.clearDisplay();
			}

			void show() override {
				_adafruit.display();
			}

			void drawRectangle(Bounds& bounds, const Color& color) override {
				_adafruit.fillRect(
					(int16_t) bounds.getX(),
					(int16_t) bounds.getY(),
					(int16_t) bounds.getWidth(),
					(int16_t) bounds.getHeight(),
					color.toUint32() > 0 ? WHITE : BLACK
				);
			}

			void drawText(Point& position, const Color& color, const String& text) override {
				_adafruit.setTextColor(color.toUint32() > 0 ? WHITE : BLACK);
				_adafruit.setCursor((int16_t) position.getX(), (int16_t) position.getY());
				_adafruit.print(text);
			}

		private:
			Adafruit_SSD1306 _adafruit;

	};
}
