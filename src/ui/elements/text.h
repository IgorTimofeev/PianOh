#pragma once

#include "element.h"
#include "ui/color.h"
#include "ui/display.h"
#include "ui/geometry/bounds.h"
#include "Fonts/Org_01.h"

namespace ui {
	class Text : public Element {
		public:
			Size onMeasure(Display& display, const Size& size) override {
				auto textBounds = display.measureText(getText());

				return {
					textBounds.getWidth(),
					textBounds.getHeight()
				};
			}

			void render(Display& display) override {
//				display.drawText(getBounds().getPosition(), getColor(), getText());

				display.drawRectangle(getBounds(), Color::white);
				display.drawText(getBounds().getPosition(), Color::black, getText());
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

		private:
			String _text;
			Color _color = Color::white;
	};
}
