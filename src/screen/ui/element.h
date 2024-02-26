#pragma once

#include <cstdint>
#include "screen/ui/geometry/margin.h"
#include "screen/ui/geometry/bounds.h"
#include "screen/ui/geometry/size.h"
#include <limits>

namespace ui {
	enum Alignment: uint8_t {
		Start,
		Center,
		End,
		Stretch,
	};

	enum Orientation: uint8_t {
		Horizontal,
		Vertical,
	};

	class Display;

	class Element {
		public:
			Element() = default;

			virtual ~Element() = default;

			Size measure(const Bounds& bounds) {
//				if (!isMeasured()) {
					setCalculatedSize(onMeasure(bounds));

//					setMeasured(true);
//				}

				return getCalculatedSize();
			}

			void arrange(const Bounds& bounds) {
//				if (isArranged())
//					return;

				auto margin = getMargin();

				int32_t x = bounds.point.getX();
				int32_t y = bounds.point.getY();

				uint16_t width = getSize().getWidth();
				uint16_t height = getSize().getHeight();

				if (width == Size::calculated) {
					width -= (margin.getLeft() - margin.getRight());
				}

				if (height == Size::calculated) {
					height -= (margin.getTop() - margin.getBottom());
				}

				switch (getHorizontalAlignment()) {
					case Start:
						x += margin.getLeft();
						break;

					case Center:
						x += (margin.getLeft() + bounds.size.getWidth() / 2 - width / 2 - margin.getRight());
						break;

					case Stretch:
						x += margin.getLeft();
						break;

					case End:
						x += (width - margin.getRight());
						break;
				}

				switch (getVerticalAlignment()) {
					case Start:
						y += margin.getTop();
						break;

					case Center:
						x += (margin.getTop() + bounds.size.getHeight() / 2 - height / 2 - margin.getBottom());
						break;

					case End:
						y += (height - margin.getBottom());
						break;

					case Stretch:
						y += margin.getTop();
						break;
				}

				setCalculatedPosition(Point(x, y));

				onArrange(Bounds(x, y, width, height));

//				setArranged(true);
			}

			virtual void render(Display& display) {

			}

			// -------------------------------- Getters & setters --------------------------------

			Alignment getHorizontalAlignment() const {
				return _horizontalAlignment;
			}

			void setHorizontalAlignment(Alignment value) {
				_horizontalAlignment = value;
			}

			Alignment getVerticalAlignment() const {
				return _verticalAlignment;
			}

			void setVerticalAlignment(Alignment value) {
				_verticalAlignment = value;
			}

			const Margin& getMargin() {
				return _margin;
			}

			void setMargin(const Margin& value) {
				_margin = value;
			}

			const Size& getSize() {
				return _size;
			}

			void setSize(const Size& value) {
				_size = value;
			}

			const Point& getCalculatedPosition() const {
				return _calculatedPosition;
			}

			const Size& getCalculatedSize() const {
				return _calculatedSize;
			}

			void debugPrintBounds() const {
				Serial.print("bounds: ");
				getCalculatedPosition().debugPrint();
				Serial.print(", size: ");
				getCalculatedSize().debugPrint();
			}

		protected:
			virtual Size onMeasure(const Bounds& bounds) {
				return getSize();
			}

			virtual void onArrange(const Bounds& bounds) {

			}

			bool isMeasured() const {
				return _isMeasured;
			}

			void setMeasured(bool value) {
				_isMeasured = value;
			}

			bool isArranged() const {
				return _isArranged;
			}

			void setArranged(bool value) {
				_isArranged = value;
			}

			void setNotMeasuredAndArranged() {
				setMeasured(false);
				setArranged(false);
			}

		private:
			Size _size = Size();
			Alignment _horizontalAlignment = Alignment::Stretch;
			Alignment _verticalAlignment = Alignment::Stretch;
			Margin _margin = Margin();

			bool _isMeasured = false;
			bool _isArranged = false;
			Point _calculatedPosition = Point();
			Size _calculatedSize = Size();

			void setCalculatedPosition(Point value) {
				_calculatedPosition = value;
			}

			void setCalculatedSize(Size value) {
				_calculatedSize = value;
			}
	};
}