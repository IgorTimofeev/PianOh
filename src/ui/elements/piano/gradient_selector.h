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

		protected:
			void onRender(Display &display) override {
				if (!_gradient)
					return;

				auto bounds = getBounds();

				// Stops
				GradientStop* stop;
				String text;
				int32_t x;

				for (size_t i = 0; i < _gradient->getStops().size(); i++) {
					stop = &_gradient->getStops()[i];

					x = bounds.getX() + (int32_t) (stop->getPosition() * (float) bounds.getWidth());

					// Line
					display.drawFastVLine(
						Point(x, bounds.getY()),
						bounds.getHeight() - _gripRadius * 2,
						Color::black
					);

					// Ellipse
					display.drawCircle(
						Point(x, bounds.getY2() - _gripRadius),
						i == _selectedIndex ? _gripRadius + 1 : _gripRadius,
						Color::black
					);

					display.drawCircle(
						Point(x, bounds.getY2() - _gripRadius),
						_gripRadius - 1,
						stop->getColor()
					);
				}
			}

			void onEvent(Event &event) override {
				if (event.getType() != EventType::touchDown && event.getType() != EventType::touchDrag && event.getType() != EventType::touchUp)
					return;

				auto touchEvent = (TouchEvent&) event;
				auto bounds = getBounds();

				if (event.getType() == EventType::touchDown) {
					auto position = Number::clampFloat((float) (touchEvent.getPosition().getX() - bounds.getX()) / (float) bounds.getWidth());

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

					setCaptured(true);
				}
				else if (event.getType() == EventType::touchDrag) {
					auto& stop = _gradient->getStops()[_selectedIndex];
					auto position = Number::clampFloat((float) (touchEvent.getPosition().getX() - bounds.getX()) / (float) bounds.getWidth());

					stop.setPosition(position);
					invalidate();
				}
				else if (event.getType() == EventType::touchUp) {
					setCaptured(false);
				}

				event.setHandled(true);
			}

		private:
			uint16_t _gripRadius = 16;
			uint16_t _selectedIndex = 0;
			LinearGradient* _gradient = nullptr;
	};
}
