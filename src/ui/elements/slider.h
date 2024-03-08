#pragma once

#include "ui/elements/element.h"
#include "ui/color.h"
#include "ui/display.h"
#include "cmath"
#include "ui/action.h"

namespace ui {
	class Slider : public Element {
		public:
			bool onEvent(ui::TouchEvent &event) override {
				auto bounds = getBounds();
				auto part = (float) (event.getX() - bounds.getX()) / (float) bounds.getWidth();

				if (part >= 0 && part <= 1)
					setValue(part);

				return true;
			}

			void render(Display& display) override {
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

			const Color &getBackground() const {
				return _background;
			}

			void setBackground(const Color &value) {
				_background = value;
			}

			const Color &getForeground() const {
				return _foreground;
			}

			void setForeground(const Color &value) {
				_foreground = value;
			}

			float getValue() const {
				return _value;
			}

			void setValue(float value) {
				_value = value;

				clampValue();
				invalidateLayout();

				_onValueChanged.invoke();
			}

			virtual void addOnValueChanged(const std::function<void()>& handler) {
				_onValueChanged.add(handler);
			}

		private:
			Color _background = Color::gray;
			Color _foreground = Color::white;
			float _value = 1;
			uint16_t _cornerRadius = 0;

			Action<> _onValueChanged {};

			void clampValue() {
				_value = Number::clampFloat(_value, 0, 1);
			}
	};
}
