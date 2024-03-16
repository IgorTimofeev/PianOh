#pragma once

#include "element.h"
#include "grafica/color.h"
#include "grafica/screen.h"
#include "grafica/bounds.h"
#include "text_aware.h"
#include "foreground_aware.h"
#include "font_aware.h"

namespace grafica {
	class Text : public TextAware, public FontAware, public ForegroundAware {
		public:
			Size onMeasure(Screen& display, const Size& availableSize) override {
				display.setFont(getFont());

				return display.measureText(getText());
			}

			void onRender(Screen& display) override {
//				display.drawRectangle(getBounds(), Color::gold);

				display.setFont(getFont());
				display.renderText(getBounds().getPosition(), getForeground(), getText());
			}
	};
}
