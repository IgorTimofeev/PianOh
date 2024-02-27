#pragma once

#include "ui/elements/element.h"
#include "ui/color.h"
#include "ui/display.h"
#include "cmath"

namespace ui {
	class Slider : public Element {
		public:
			void render(Display& display) override {
				auto bounds = getBounds();

				auto position = (uint16_t) roundf(_value / (_maximum - _minimum));

				display.drawRectangle(
					Bounds(
						bounds.getPosition(),
						Size(
							position,
							bounds.getHeight()
						)
					),
					_cornerRadius,
					getBackground()
				);

				display.drawRectangle(
					Bounds(
						Point(
							bounds.getX() + position,
							bounds.getY()
						),
						Size(
							bounds.getWidth() - position,
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

			float getMinimum() const {
				return _minimum;
			}

			void setMinimum(float value) {
				_minimum = value;

				if (_minimum > _maximum)
					_minimum = _maximum;

				clampValue();
			}

			float getMaximum() const {
				return _maximum;
			}

			void setMaximum(float value) {
				_maximum = value;

				if (_maximum < _minimum)
					_maximum = _minimum;

				clampValue();
			}

			float getValue() const {
				return _value;
			}

			void setValue(float value) {
				_value = value;

				clampValue();
			}
		private:
			Color _background = Color::black;
			Color _foreground = Color::white;
			float _minimum = 0;
			float _maximum = 1;
			float _value = 1;
			uint16_t _cornerRadius = 0;

			void clampValue() {
				_value = Number::clampFloat(_value, _minimum, _maximum);
			}
	};
}
