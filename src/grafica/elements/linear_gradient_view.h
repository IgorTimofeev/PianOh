#pragma once

#include "element.h"
#include "grafica/display.h"
#include "grafica/color.h"
#include "grafica/gradient.h"

namespace grafica {
	class LinearGradientView : public Element {
		public:
			uint16_t getSelectedIndex() const {
				return _selectedIndex;
			}

			void setSelectedIndex(uint16_t selectedIndex) {
				_selectedIndex = selectedIndex;
			}

			LinearGradient *getGradient() const {
				return _gradient;
			}

			void setGradient(LinearGradient *gradient) {
				_gradient = gradient;
			}

		protected:
			void render(Display &display) override {
				if (!_gradient)
					return;

				auto bounds = getBounds();

				float position = 0;
				float positionStep = 1.0f / (float) bounds.getWidth();

				// Background
				for (int32_t x = bounds.getX(); x < bounds.getX() + bounds.getWidth(); x++) {
					display.drawFastVLine(
						Point(x, bounds.getY()),
						bounds.getHeight(),
						_gradient->getColor(position)
					);

					position += positionStep;
				}

				// Stops
				GradientStop* stop;
				String text;

				for (size_t i = 0; i < _gradient->getStops().size(); i++) {
					stop = &_gradient->getStops()[i];

					int32_t x = bounds.getX() + (int32_t) (stop->getPosition() * (float) bounds.getWidth());

					if (i == _selectedIndex) {
						display.drawRectangle(Bounds(x - 4, bounds.getY() - 4, 8, bounds.getHeight() + 8), Color::black);
						display.drawRectangle(Bounds(x - 3, bounds.getY() - 3, 6, bounds.getHeight() + 6), _gradient->getColor(stop->getPosition()));
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

			bool onEvent(Event &event) override {
				if (event.getType() != EventType::touchDown && event.getType() != EventType::touchDrag)
					return false;

				auto touchEvent = (TouchEvent&) event;

				auto bounds = getBounds();
				auto position = (float) (touchEvent.getPosition().getX() - bounds.getX()) / (float) bounds.getWidth();

				if (position >= 0 && position <= 1) {
					uint16_t closestIndex = 0;
					float closestDelta = 99999;
					float delta;

					GradientStop* stop;

					for (size_t i = 0; i < _gradient->getStops().size(); i++) {
						stop = &_gradient->getStops()[i];
						delta = abs(stop->getPosition() - position);

						if (delta < closestDelta) {
							closestDelta = delta;
							closestIndex = i;
						}
					}

					_selectedIndex = closestIndex;
					invalidate();
				}

				return true;
			}

		private:
			uint16_t _selectedIndex = 0;
			LinearGradient* _gradient = nullptr;
	};
}
