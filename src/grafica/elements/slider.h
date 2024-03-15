#pragma once

#include "element.h"
#include "grafica/color.h"
#include "grafica/display.h"
#include "cmath"
#include "grafica/action.h"
#include "background_aware.h"
#include "foreground_aware.h"

namespace grafica {
	class Slider : public BackgroundAware, public ForegroundAware {
		public:
			Slider() {
				setBackground(Color::black);
				setForeground(Color::gray);
			}

			void onEvent(Event &event) override {
				if (event.getType() != EventType::touchDown && event.getType() != EventType::touchDrag && event.getType() != EventType::touchUp)
					return;

				auto touchEvent = (TouchEvent&) event;

				if (event.getType() == EventType::touchDown) {
					setCaptured(true);
				}
				else if (event.getType() == EventType::touchUp) {
					setCaptured(false);
				}

				auto bounds = getBounds();
				auto part = Number::clampFloat((float) (touchEvent.getPosition().getX() - bounds.getX()) / (float) bounds.getWidth());

				setValue(part);

				event.setHandled(true);
			}

			void onRender(Display& display) override {
				auto bounds = getBounds();
				auto part = (uint16_t) round(_value * (float) bounds.getWidth());

				display.drawRectangle(
					bounds,
					_cornerRadius,
					getBackground()
				);

				display.drawRectangle(
					Bounds(
						bounds.getPosition(),
						Size(
							part,
							bounds.getHeight()
						)
					),
					_cornerRadius,
					getForeground()
				);
			}

			// -------------------------------- Getters & setters --------------------------------

			uint16_t getCornerRadius() const {
				return _cornerRadius;
			}

			void setCornerRadius(uint16_t value) {
				_cornerRadius = value;
			}

			float getValue() const {
				return _value;
			}

			void setValue(float value) {
				_value = value;

				clampValue();
				invalidateRender();

				_onValueChanged.invoke();
			}

			virtual void addOnValueChanged(const std::function<void()>& handler) {
				_onValueChanged.add(handler);
			}

		private:
			float _value = 1;
			uint16_t _cornerRadius = 0;

			Action<> _onValueChanged {};

			void clampValue() {
				_value = Number::clampFloat(_value, 0, 1);
			}
	};
}
