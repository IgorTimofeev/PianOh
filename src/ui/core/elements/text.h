#pragma once

#include "element.h"
#include "ui/core/color.h"
#include "ui/core/display.h"
#include "ui/core/bounds.h"

namespace ui {
	class Text : public Element {
		public:
			Size onMeasure(Display& display, const Size& availableSize) override {
				return display.measureText(getText(), getFontSize());
			}

			void render(Display& display) override {
//				display.drawRectangle(getBounds(), Color::gold);
				display.drawText(getBounds().getPosition(), getColor(), getText(), getFontSize());
			}

			// -------------------------------- Getters & setters --------------------------------

			const String &getText() const {
				return _text;
			}

			void setText(const String& value) {
				_text = value;

				invalidateLayout();
			}

			const Color &getColor() const {
				return _color;
			}

			void setColor(const Color& value) {
				_color = value;
			}

			uint8_t getFontSize() const {
				return _fontSize;
			}

			void setFontSize(uint8_t value) {
				_fontSize = value;
			}

		private:
			String _text;
			uint8_t _fontSize = 2;
			Color _color = Color::black;
	};
}
