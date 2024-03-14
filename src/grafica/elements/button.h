#pragma once

#include "element.h"
#include "grafica/color.h"
#include "grafica/display.h"
#include "background_aware.h"
#include "foreground_aware.h"
#include "text_aware.h"

namespace grafica {
	class Button : public TextAware, public BackgroundAware, public ForegroundAware {
		public:
			void addOnClick(const std::function<void()>& value) {
				_onClick.add(value);
			}

		public:
			void render(Display &display) override {
				auto& bounds = getBounds();
				auto& text = getText();
				auto textSize = display.measureText(text, getFontSize());

				display.drawRectangle(bounds, getBackground());

				display.drawText(
					Point(
						bounds.getX() + bounds.getWidth() / 2 - textSize.getWidth() / 2,
						bounds.getY() + bounds.getHeight() / 2 - textSize.getHeight() / 2
					),
					getForeground(),
					text,
					getFontSize()
				);
			}

			bool onEvent(Event &event) override {
				if (event.getType() != EventType::touchDown && event.getType() != EventType::touchDrag)
					return false;

				_onClick.invoke();

				return true;
			}

		private:
			Action<> _onClick {};
	};
}
