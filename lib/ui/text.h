#pragma once

#include "element.h"
#include "color.h"
#include "display.h"
#include "geometry/bounds.h"
#include "Fonts/Org_01.h"

namespace ui {
	class Text : public Element {
		public:
			Size onMeasure(const Size& size) override {
				return {
					(uint16_t) (16 * getText().length()),
					16
				};
			}

			void render(Display& display) override {
//				display.drawText(getBounds().point, getColor(), getText());

//				display.drawRectangle(getBounds(), Color::white);
				display.drawText(getBounds().point, Color::white, getText());
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
			Color _color = Color::white;
	};
}
