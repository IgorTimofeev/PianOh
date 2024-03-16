#pragma once

#include "element.h"
#include "grafica/color.h"
#include "grafica/screen.h"
#include "grafica/bounds.h"
#include "text_aware.h"
#include "foreground_aware.h"

namespace grafica {
	class Text : public TextAware, public ForegroundAware {
		public:
			Size onMeasure(Screen& display, const Size& availableSize) override {
				return display.measureText(getText(), getFontSize());
			}

			void onRender(Screen& display) override {
//				display.drawRectangle(getBounds(), Color::gold);
				display.drawText(getBounds().getPosition(), getForeground(), getText(), getFontSize());
			}
	};
}
