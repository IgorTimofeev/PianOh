#pragma once

#include "ui/elements/shape.h"
#include "ui/elements/stack_layout.h"
#include "ui/color.h"
#include "ui/display.h"
#include "cmath"

namespace ui {
	class SevenSegment : public Element {
		public:
			Size onMeasure(ui::Display &display, const ui::Size &availableSize) override {
				return {
					(uint16_t) (((getDigitWidth() + getSpacing()) * getDigitCount()) - getSpacing()),
					getDigitHeight()
				};
			}

			void render(Display& display) override {
				auto bounds = getBounds();
				auto position = Point(bounds.getX() + ((getDigitWidth() + getSpacing()) * getDigitCount()) - getSpacing(), bounds.getY());
				auto value = getValue();
				float govno;

				for (uint8_t i = 0; i < getDigitCount(); i++) {
					if (value > 0) {
						govno = (float) value / 10.0f;
						drawDigit(display, position, (uint8_t) ((govno - floor(govno)) * 10));

						value /= 10;
					}
					else {
						drawDigit(display, position, 0);
					}

					position.setX(position.getX() - getDigitWidth() - getSpacing());
				}
			}

			// -------------------------------- Getters & setters --------------------------------

			uint8_t getSegmentThickness() const {
				return _segmentThickness;
			}

			void setSegmentThickness(uint8_t value) {
				_segmentThickness = value;

				invalidateLayout();
			}

			uint8_t getSegmentLength() const {
				return _segmentLength;
			}

			void setSegmentLength(uint8_t value) {
				_segmentLength = value;

				invalidateLayout();
			}

			const Color &getColorOff() const {
				return _colorOff;
			}

			void setColorOff(const Color &value) {
				_colorOff = value;
			}

			const Color &getColorOn() const {
				return _colorOn;
			}

			void setColorOn(const Color &value) {
				_colorOn = value;
			}

			uint32_t getValue() const {
				return _value;
			}

			void setValue(uint32_t value) {
				_value = value;

				invalidateLayout();
			}

			uint8_t getDigitCount() const {
				return _digitCount;
			}

			void setDigitCount(uint8_t value) {
				_digitCount = value;

				invalidateLayout();
			}

			uint8_t getSpacing() const {
				return _spacing;
			}

			void setSpacing(uint8_t value) {
				_spacing = value;

				invalidateLayout();
			}

			uint16_t getDigitWidth() const {
				return (uint16_t) (getSegmentThickness() * 2 + getSegmentLength());
			}

			uint16_t getDigitHeight() const {
				return (uint16_t) (getSegmentThickness() * 3 + getSegmentLength() * 2);
			}

		private:
			Color _colorOff = Color::black;
			Color _colorOn = Color::white;
			uint32_t _value = 0;
			uint8_t _digitCount = 1;
			uint8_t _spacing = 3;
			uint8_t _segmentThickness = 3;
			uint8_t _segmentLength = 9;

			void drawSegments(
				Display& display,
				const Point& position,
				bool s0,
				bool s1,
				bool s2,
				bool s3,
				bool s4,
				bool s5,
				bool s6
			) const {
				uint8_t t = getSegmentThickness();
				uint8_t l = getSegmentLength();

				display.drawRectangle(Bounds(position.getX() + t, position.getY(), l, t), s0 ? getColorOn() : getColorOff());
				display.drawRectangle(Bounds(position.getX() + t + l, position.getY() + t, t, l), s1 ? getColorOn() : getColorOff());
				display.drawRectangle(Bounds(position.getX() + t + l, position.getY() + t + l + t, t, l), s2 ? getColorOn() : getColorOff());
				display.drawRectangle(Bounds(position.getX() + t, position.getY() + (t + l) * 2, l, t), s3 ? getColorOn() : getColorOff());
				display.drawRectangle(Bounds(position.getX(), position.getY() + t + l + t, t, l), s4 ? getColorOn() : getColorOff());
				display.drawRectangle(Bounds(position.getX(), position.getY() + t, t, l), s5 ? getColorOn() : getColorOff());
				display.drawRectangle(Bounds(position.getX() + t, position.getY() + t + l, l, t), s6 ? getColorOn() : getColorOff());
			}

			void drawDigit(Display& display, const Point& position, uint8_t digit) {
				switch (digit) {
					case 0:
						drawSegments(
							display,
							position,
							true,
							true,
							true,
							true,
							true,
							true,
							false
						);

						break;

					case 1:
						drawSegments(
							display,
							position,
							false,
							true,
							true,
							false,
							false,
							false,
							false
						);

						break;

					case 2:
						drawSegments(
							display,
							position,
							true,
							true,
							false,
							true,
							true,
							false,
							true
						);

						break;

					case 3:
						drawSegments(
							display,
							position,
							true,
							true,
							true,
							true,
							false,
							false,
							true
						);

						break;

					case 4:
						drawSegments(
							display,
							position,
							false,
							true,
							true,
							false,
							false,
							true,
							true
						);

						break;

					case 5:
						drawSegments(
							display,
							position,
							true,
							false,
							true,
							true,
							false,
							true,
							true
						);

						break;

					case 6:
						drawSegments(
							display,
							position,
							true,
							false,
							true,
							true,
							true,
							true,
							true
						);

						break;

					case 7:
						drawSegments(
							display,
							position,
							true,
							true,
							true,
							false,
							false,
							false,
							false
						);

						break;

					case 8:
						drawSegments(
							display,
							position,
							true,
							true,
							true,
							true,
							true,
							true,
							true
						);

						break;

					default:
						drawSegments(
							display,
							position,
							true,
							true,
							true,
							true,
							false,
							true,
							true
						);

						break;
				}
			}
	};
}
