#pragma once

#include <cstdint>
#include "ui/geometry/thickness.h"
#include "ui/geometry/rectangle.h"
#include "ui/geometry/size.h"
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

	class Element {
		public:
			Element() = default;

			virtual ~Element() = default;

			void arrange(const Rectangle& bounds) {
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
				setCalculatedSize(Size(width, height));

				onArrange(Rectangle(x, y, width, height));
			}

			const Size& measure(const Rectangle& bounds)  {
				return onMeasure(bounds);
			}

			virtual void render()  {

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

			const Thickness& getMargin() {
				return _margin;
			}

			void setMargin(const Thickness& value) {
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

			void setCalculatedPosition(const Point& value) {
				_calculatedPosition = value;
			}

			const Size& getCalculatedSize() const {
				return _calculatedSize;
			}

			void setCalculatedSize(const Size& value) {
				_calculatedSize = value;
			}

		protected:
			virtual const Size& onMeasure(const Rectangle& bounds) {
				return getSize();
			}

			virtual void onArrange(const Rectangle& bounds) {

			}

		private:
			Size _size = Size();
			Alignment _horizontalAlignment = Alignment::Stretch;
			Alignment _verticalAlignment = Alignment::Stretch;
			Thickness _margin = Thickness();

			Point _calculatedPosition = Point();
			Size _calculatedSize = Size();
	};
}