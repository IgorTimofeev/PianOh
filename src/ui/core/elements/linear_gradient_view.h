#pragma once

#include "element.h"
#include "ui/core/display.h"
#include "ui/core/color.h"
#include "ui/core/gradient.h"

namespace ui {
	class LinearGradientView : public Element {
		public:
			LinearGradientView() {
				gradient.addRainbowStops();
			}

		protected:
			void render(Display &display) override {
				auto bounds = getBounds();

				float position = 0;
				float positionStep = 1.0f / (float) bounds.getWidth();

				// Background
				for (int32_t x = bounds.getX(); x < bounds.getX() + bounds.getWidth(); x++) {
					display.drawFastVLine(
						Point(x, bounds.getY()),
						bounds.getHeight(),
						gradient.getColor(position)
					);

					position += positionStep;
				}

				// Stops
				GradientStop* stop;
				String text;

				for (size_t i = 0; i < gradient.getStops().size(); i++) {
					stop = &gradient.getStops()[i];

					int32_t x = bounds.getX() + (int32_t) (stop->getPosition() * (float) bounds.getWidth());

					if (i == selectedIndex) {
						display.drawRectangle(Bounds(x - 4, bounds.getY() - 4, 8, bounds.getHeight() + 8), Color::black);
						display.drawRectangle(Bounds(x - 3, bounds.getY() - 3, 6, bounds.getHeight() + 6), gradient.getColor(stop->getPosition()));
					}
					else {
						display.drawRectangle(Bounds(x, bounds.getY(), 1, bounds.getHeight()), Color::black);
					}

					text = String(((uint8_t) round(stop->getPosition() * 100)));

					display.drawText(
						Point(
							x - display.measureText(text, 1).getWidth() / 2,
							bounds.getY() + bounds.getHeight() + 10
						),
						Color::black,
						text,
						1
					);
				}
			}

			bool onEvent(TouchEvent &event) override {
				auto bounds = getBounds();
				auto position = (float) (event.getX() - bounds.getX()) / (float) bounds.getWidth();

				if (position >= 0 && position <= 1) {
					uint16_t closestIndex = 0;
					float closestDelta = 99999;
					float delta;

					GradientStop* stop;

					for (size_t i = 0; i < gradient.getStops().size(); i++) {
						stop = &gradient.getStops()[i];
						delta = abs(stop->getPosition() - position);

						if (delta < closestDelta) {
							closestDelta = delta;
							closestIndex = i;
						}
					}

					selectedIndex = closestIndex;
					invalidateLayout();
				}

				return true;
			}

		private:
			uint16_t selectedIndex = 0;
			LinearGradient gradient = LinearGradient();
	};
}
