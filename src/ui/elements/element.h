#pragma once

#include <cstdint>
#include "ui/geometry/margin.h"
#include "ui/geometry/bounds.h"
#include "ui/geometry/size.h"
#include <limits>
#include "ui/elements/workspace.h"

namespace ui {
	enum Alignment: uint8_t {
		start,
		center,
		end,
		stretch,
	};

	enum Orientation: uint8_t {
		horizontal,
		vertical,
	};

	class Display;

	class Element {
		public:
			Element() = default;

			virtual ~Element() = default;

			virtual void invalidateLayout() {
				if (_firstParent)
					_firstParent->invalidateLayout();
			}

			Size measure(Display& display, const Size& constraint) {
				auto desiredSize = onMeasure(display, constraint);
				auto margin = getMargin();

				desiredSize.setWidth(desiredSize.getWidth() + margin.getLeft() + margin.getRight());
				desiredSize.setHeight(desiredSize.getHeight() + margin.getTop() + margin.getBottom());

				setDesiredSize(desiredSize);

				return desiredSize;
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
					case start:
						if (size == Size::calculated) {
							newSize = desiredSize;
						}
						else {
							newSize = size;
						}

						newPosition = position + marginStart;

						break;

					case center:
						if (size == Size::calculated) {
							newSize = desiredSize;
						}
						else {
							newSize = size;
						}

						newPosition = position + limit / 2 - newSize / 2 + marginStart - marginEnd;

						break;

					case end:
						if (size == Size::calculated) {
							newSize = desiredSize;
						}
						else {
							newSize = size;
						}

						newPosition = position + limit - marginEnd - newSize;

						break;

					case stretch:
						if (size == Size::calculated) {
							newSize = max(limit - marginStart - marginEnd, 0);
						}
						else {
							newSize = size;
						}

						newPosition = position + marginStart;

						break;
				}
			}

			void arrange(const Bounds& bounds) {
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

				Serial.print(newPosition);
				Serial.print(" x ");
				Serial.println(newSize);

				newBounds.setY(newPosition);
				newBounds.setHeight(newSize);

				setBounds(newBounds);
				onArrange(newBounds);
			}

			virtual void render(Display& display) {

			}

			// -------------------------------- Getters & setters --------------------------------

			Alignment getHorizontalAlignment() const {
				return _horizontalAlignment;
			}

			void setHorizontalAlignment(Alignment value) {
				_horizontalAlignment = value;

				invalidateLayout();
			}

			Alignment getVerticalAlignment() const {
				return _verticalAlignment;
			}

			void setVerticalAlignment(Alignment value) {
				_verticalAlignment = value;

				invalidateLayout();

			}

			const Margin& getMargin() {
				return _margin;
			}

			void setMargin(const Margin& value) {
				_margin = value;

				invalidateLayout();
			}

			const Size& getSize() {
				return _size;
			}

			void setSize(const Size& value) {
				_size = value;

				invalidateLayout();
			}

			const Size& getDesiredSize() {
				return _desiredSize;
			}

			const Bounds& getBounds() {
				return _bounds;
			}

			Element* getFirstParent() {
				return _firstParent;
			}

			void setFirstParent(Element* value) {
				_firstParent = value;
			}

			Element* getParent() {
				return _parent;
			}

			void setParent(Element* value) {
				_parent = value;
			}

		protected:
			virtual Size onMeasure(Display& display, const Size& constraint) {
				return {
					constraint.getWidth() == Size::infinity ? (uint16_t) 0 : constraint.getWidth(),
					constraint.getHeight() == Size::infinity ? (uint16_t) 0 : constraint.getHeight()
				};
			}

			virtual void onArrange(const Bounds& bounds) {

			}

		private:
			Size _size = Size(Size::calculated, Size::calculated);
			Alignment _horizontalAlignment = Alignment::stretch;
			Alignment _verticalAlignment = Alignment::stretch;
			Margin _margin = Margin();
			Element* _firstParent = nullptr;
			Element* _parent = nullptr;

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