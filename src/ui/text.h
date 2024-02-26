#pragma once

#include "element.h"
#include "color.h"
#include "geometry/rectangle.h"

namespace ui {
	class Text : public Element {
		public:
			Text() = default;

			const Size& onMeasure(const Rectangle& bounds) override {
				return Size(16 * getText().length(), 16);
			}

			void render() override {
				// Screen.drawText
			}

			// -------------------------------- Getters & setters --------------------------------

			const String &getText() const {
				return _text;
			}

			void setText(const String& value) {
				_text = value;
			}

			const Color &getColor() const {
				return _color;
			}

			void setColor(const Color& value) {
				_color = value;
			}

		private:
			String _text;
			Color _color;
	};
}
