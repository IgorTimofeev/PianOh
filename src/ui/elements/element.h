#pragma once

#include <cstdint>
#include "ui/geometry/margin.h"
#include "ui/geometry/bounds.h"
#include "ui/geometry/size.h"
#include <limits>
#include "ui/elements/workspace.h"

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

			const Size& measure(Display& display, const Size& constraint) {
				setDesiredSize(onMeasure(display, constraint));

				return getDesiredSize();
			}

			static void calculateShit(
				const Alignment& alignment,
				const int32_t& position,
				const uint16_t& size,
				const uint16_t& desiredSize,
				const uint16_t& marginStart,
				const uint16_t& marginEnd,
				const uint16_t& limit,
				int32_t& newPosition,
				int32_t& newSize
			) {
				switch (alignment) {
					case Start:
						if (size == Size::calculated) {
							newSize = desiredSize;
						}
						else {
							newSize = size;
						}

						newPosition = position + marginStart;

						break;

					case Center:
						if (size == Size::calculated) {
							newSize = desiredSize;
						}
						else {
							newSize = size;
						}

						newPosition = position + limit / 2 - newSize / 2 + marginStart - marginEnd;

						break;

					case End:
						if (size == Size::calculated) {
							newSize = desiredSize;
						}
						else {
							newSize = size;
						}

						newPosition = position + limit - marginEnd - newSize;

						break;

					case Stretch:
						if (size == Size::calculated) {
							auto marginValue = marginStart + marginEnd;

							newSize =
								marginValue > limit
								? 0
								: limit - marginValue;
						}
						else {
							newSize = size;
						}

						newPosition = position + marginStart;

						break;
				}
			}

			void arrange(const Bounds& bounds) {
//				if (isArranged())
//					return;

				auto margin = getMargin();
				auto desiredSize = getDesiredSize();
				auto size = getSize();

				Bounds newBounds;
				int32_t newPosition = 0;
				int32_t newSize = 0;

				calculateShit(
					getHorizontalAlignment(),
					bounds.getX(),
					size.getWidth(),
					desiredSize.getWidth(),
					margin.getLeft(),
					margin.getRight(),
					bounds.getWidth(),
					newPosition,
					newSize
				);

				newBounds.setX(newPosition);
				newBounds.setWidth(newSize);

				calculateShit(
					getVerticalAlignment(),
					bounds.getY(),
					size.getHeight(),
					desiredSize.getHeight(),
					margin.getTop(),
					margin.getBottom(),
					bounds.getHeight(),
					newPosition,
					newSize
				);

				newBounds.setY(newPosition);
				newBounds.setHeight(newSize);

				setBounds(newBounds);
				onArrange(newBounds);

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


			const Size& getDesiredSize() {
				return _desiredSize;
			}

			const Bounds& getBounds() {
				return _bounds;
			}

			virtual void invalidateLayout() {
				if (_firstParent)
					_firstParent->invalidateLayout();
			}

			Element* getFirstParent() {
				return _firstParent;
			}

			void setFirstParent(Element* value) {
				_firstParent = value;
			}

		protected:
			virtual Size onMeasure(Display& display, const Size& constraint) {
				return getSize();
			}

			virtual void onArrange(const Bounds& bounds) {

			}

		private:
			Size _size = Size(Size::calculated, Size::calculated);
			Alignment _horizontalAlignment = Alignment::Stretch;
			Alignment _verticalAlignment = Alignment::Stretch;
			Margin _margin = Margin();
			Element* _firstParent = nullptr;

			Bounds _bounds;
			Size _desiredSize = Size();

			void setDesiredSize(const Size& value) {
				_desiredSize = value;
			}

			void setBounds(const Bounds& value) {
				_bounds = value;
			}
	};
}