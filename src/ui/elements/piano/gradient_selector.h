#pragma once

#include "grafica/elements/element.h"
#include "grafica/display.h"
#include "grafica/color.h"
#include "grafica/gradient.h"

namespace grafica {
	class GradientSelector : public Element {
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

			uint16_t getGripRadius() const {
				return _gripRadius;
			}

			void setGripRadius(uint16_t gripRadius) {
				_gripRadius = gripRadius;
			}

			uint16_t getTextSpacing() const {
				return _textSpacing;
			}

			void setTextSpacing(uint16_t textSpacing) {
				_textSpacing = textSpacing;
			}

		protected:
			void onRender(Display &display) override {
				if (!_gradient)
					return;

				auto bounds = getBounds();

				// Stops
				GradientStop* stop;
				String text;
				Size textSize;
				int32_t x;
				int32_t y;

				for (size_t i = 0; i < _gradient->getStops().size(); i++) {
					stop = &_gradient->getStops()[i];

					text = String(((uint8_t) round(stop->getPosition() * 100)));
					textSize = display.measureText(text, 1);

					x = bounds.getX() + (int32_t) (stop->getPosition() * (float) bounds.getWidth());
					y = bounds.getY2() - textSize.getHeight() - _textSpacing - _gripRadius * 2;

					// Line
					display.drawFastVLine(
						Point(x, bounds.getY()),
						y - bounds.getY(),
						Color::black
					);

					// Ellipse
					y += _gripRadius;

					display.drawCircle(
						Point(x, y),
						i == _selectedIndex ? _gripRadius + 1 : _gripRadius,
						Color::black
					);

					display.drawCircle(
						Point(x, y),
						_gripRadius - 1,
						stop->getColor()
					);

					y += _gripRadius + _textSpacing;

					display.drawText(
						Point(
							x - textSize.getWidth() / 2,
							y
						),
						Color::black,
						text,
						1
					);
				}
			}

			void onEvent(Event &event) override {
				if (event.getType() != EventType::touchDown && event.getType() != EventType::touchDrag)
					return;

				auto touchEvent = (TouchEvent&) event;
				auto bounds = getBounds();

				if (event.getType() == EventType::touchDown) {
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
				}
				else if (event.getType() == EventType::touchDrag) {
					auto& stop = _gradient->getStops()[_selectedIndex];
					auto position = (float) (touchEvent.getPosition().getX() - bounds.getX()) / (float) bounds.getWidth();

					stop.setPosition(position);
					invalidate();
				}

				event.setHandled(true);
			}

		private:
			uint16_t _gripRadius = 16;
			uint16_t _textSpacing = 10;
			uint16_t _selectedIndex = 0;
			LinearGradient* _gradient = nullptr;
	};
}
