#pragma once

#include "ui/elements/shape.h"
#include "ui/elements/stack_layout.h"
#include "ui/color.h"
#include "ui/display.h"
#include "cmath"

namespace ui {
	class SevenSegment : public Element {
		public:
			SevenSegment() {
				setValue(0);
			}

			Size onMeasure(ui::Display &display, const ui::Size &availableSize) override {
				return {
					(uint16_t) (getSegmentThickness() * 5),
					(uint16_t) (getSegmentThickness() * 9)
				};
			}

			void render(Display& display) override {
				auto bounds = getBounds();

				uint8_t sml = getSegmentThickness();
				uint8_t big = sml * 3;

				drawSegment(display, 0, Bounds(bounds.getX() + sml, bounds.getY(), big, sml));
				drawSegment(display, 1, Bounds(bounds.getX() + sml + big, bounds.getY() + sml, sml, big));
				drawSegment(display, 2, Bounds(bounds.getX() + sml + big, bounds.getY() + sml + big + sml, sml, big));
				drawSegment(display, 3, Bounds(bounds.getX() + sml, bounds.getY() + (sml + big) * 2, big, sml));
				drawSegment(display, 4, Bounds(bounds.getX(), bounds.getY() + sml + big + sml, sml, big));
				drawSegment(display, 5, Bounds(bounds.getX(), bounds.getY() + sml, sml, big));
				drawSegment(display, 6, Bounds(bounds.getX() + sml, bounds.getY() + sml + big, big, sml));
			}

			// -------------------------------- Getters & setters --------------------------------

			uint8_t getSegmentThickness() const {
				return _segmentThickness;
			}

			void setSegmentThickness(uint8_t value) {
				_segmentThickness = value;

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

			uint8_t getValue() const {
				return _value;
			}

			void setValue(uint8_t value) {
				_value = value;

				switch (_value) {
					case 0:
						_segments[0] = true;
						_segments[1] = true;
						_segments[2] = true;
						_segments[3] = true;
						_segments[4] = true;
						_segments[5] = true;
						_segments[6] = false;
						break;

					case 1:
						_segments[0] = false;
						_segments[1] = true;
						_segments[2] = true;
						_segments[3] = false;
						_segments[4] = false;
						_segments[5] = false;
						_segments[6] = false;
						break;

					case 2:
						_segments[0] = true;
						_segments[1] = true;
						_segments[2] = false;
						_segments[3] = true;
						_segments[4] = true;
						_segments[5] = false;
						_segments[6] = true;
						break;

					case 3:
						_segments[0] = true;
						_segments[1] = true;
						_segments[2] = true;
						_segments[3] = true;
						_segments[4] = false;
						_segments[5] = false;
						_segments[6] = true;
						break;

					case 4:
						_segments[0] = true;
						_segments[1] = true;
						_segments[2] = false;
						_segments[3] = false;
						_segments[4] = false;
						_segments[5] = true;
						_segments[6] = true;
						break;

					case 5:
						_segments[0] = true;
						_segments[1] = false;
						_segments[2] = true;
						_segments[3] = true;
						_segments[4] = false;
						_segments[5] = true;
						_segments[6] = true;
						break;

					case 6:
						_segments[0] = true;
						_segments[1] = false;
						_segments[2] = true;
						_segments[3] = true;
						_segments[4] = true;
						_segments[5] = true;
						_segments[6] = true;
						break;

					case 7:
						_segments[0] = true;
						_segments[1] = true;
						_segments[2] = true;
						_segments[3] = false;
						_segments[4] = false;
						_segments[5] = false;
						_segments[6] = false;
						break;

					case 8:
						_segments[0] = true;
						_segments[1] = true;
						_segments[2] = true;
						_segments[3] = true;
						_segments[4] = true;
						_segments[5] = true;
						_segments[6] = true;
						break;

					default:
						_segments[0] = true;
						_segments[1] = true;
						_segments[2] = true;
						_segments[3] = true;
						_segments[4] = false;
						_segments[5] = true;
						_segments[6] = true;
						break;
				}
			}

		private:
			Color _colorOff = Color::black;
			Color _colorOn = Color::white;
			uint8_t _value = 0;
			uint8_t _segmentThickness = 3;

			bool _segments[7] {
				false,
				false,
				false,
				false,
				false,
				false,
				false,
			};

			void drawSegment(Display& display, uint8_t index, const Bounds& bounds) {
				display.drawRectangle(bounds, _segments[index] ? getColorOn() : getColorOff());
			}

			void drawDigit(Display& display, const Bounds& bounds, uint8_t digit) {
				uint8_t sml = getSegmentThickness();
				uint8_t big = sml * 3;

				drawSegment(display, 0, Bounds(bounds.getX() + sml, bounds.getY(), big, sml));
				drawSegment(display, 1, Bounds(bounds.getX() + sml + big, bounds.getY() + sml, sml, big));
				drawSegment(display, 2, Bounds(bounds.getX() + sml + big, bounds.getY() + sml + big + sml, sml, big));
				drawSegment(display, 3, Bounds(bounds.getX() + sml, bounds.getY() + (sml + big) * 2, big, sml));
				drawSegment(display, 4, Bounds(bounds.getX(), bounds.getY() + sml + big + sml, sml, big));
				drawSegment(display, 5, Bounds(bounds.getX(), bounds.getY() + sml, sml, big));
				drawSegment(display, 6, Bounds(bounds.getX() + sml, bounds.getY() + sml + big, big, sml));
			}
	};

	class SevenSegmentLayout : public StackLayout {
		public:
			explicit SevenSegmentLayout(uint8_t segmentCount) {
				setOrientation(Orientation::horizontal);

				for (uint8_t i = 0; i < segmentCount; i++) {
					*this += new SevenSegment();
				}
			}

			~SevenSegmentLayout() override {
				for (auto segment : *this) {
					delete segment;
				}

				removeChildren();
			}

			void setColor(int index, const Color& value) {
				reinterpret_cast<SevenSegment *>((*this)[index])->setColorOn(value);
			}

			void setValue(int index, uint8_t value) {
				reinterpret_cast<SevenSegment*>((*this)[index])->setValue(value);
			}

			void setValue(uint32_t value) {
				float govno;

				for (uint8_t i = getChildrenCount() - 1; i > 0; i--) {
					if (value > 0) {
						govno = (float) value / 10.0f;
						setValue(i, (uint8_t) ((govno - floor(govno)) * 10));

						value /= 10;
					}
					else {
						setValue(i, 0);
					}
				}
			}

			void setSegmentSize(uint8_t value) {
				for (auto element : *this) {
					reinterpret_cast<SevenSegment *>(element)->setSegmentThickness(value);
				}
			}

		private:

	};
}
