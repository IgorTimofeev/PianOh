#pragma once

#include <cstdint>
#include "ui/geometry/margin.h"
#include "ui/geometry/bounds.h"
#include "ui/geometry/size.h"
#include <limits>

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
	class TouchEvent;

	class Element {
		public:
			Element() = default;

			virtual ~Element() = default;

			virtual void invalidateLayout() {
				if (_firstParent)
					_firstParent->invalidateLayout();
			}

			Size measure(Display& display, const Size& availableSize) {
				auto desiredSize = measureOverride(display, availableSize);

				auto size = getSize();
				auto margin = getMargin();

				if (size.getWidth() != Size::calculated) {
					desiredSize.setWidth(size.getWidth());
				}

				if (size.getHeight() != Size::calculated) {
					desiredSize.setHeight(size.getHeight());
				}

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
							newSize = max(desiredSize - marginStart - marginEnd, 0);
						}
						else {
							newSize = size;
						}

						newPosition = position + marginStart;

						break;

					case center:
						if (size == Size::calculated) {
							newSize = max(desiredSize - marginStart - marginEnd, 0);
						}
						else {
							newSize = size;
						}

						newPosition = position + limit / 2 - newSize / 2 + marginStart - marginEnd;

						break;

					case end:
						if (size == Size::calculated) {
							newSize = max(desiredSize - marginStart - marginEnd, 0);
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

				if (tag == 1) {
					Serial.print(desiredSize.getHeight());
					Serial.print(" x ");
					Serial.print(bounds.getHeight());
					Serial.print(" x ");
					Serial.print(newPosition);
					Serial.print(" x ");
					Serial.println(newSize);
				}

				newBounds.setY(newPosition);
				newBounds.setHeight(newSize);

				setBounds(newBounds);
				arrangeOverride(newBounds);
			}

			int32_t tag = 0;

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

			void setAlignment(Alignment horizontal, Alignment vertical) {
				_horizontalAlignment = horizontal;
				_verticalAlignment = vertical;

				invalidateLayout();
			}

			void setAlignment(Alignment uniformValue) {
				setAlignment(uniformValue, uniformValue);
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

			virtual void addEventHandler(const std::function<void(TouchEvent&)>& handler) {
				_eventHandlers.add(handler);
			}

			bool handleEvent(TouchEvent& event) {
				if (!(getBounds().intersectsWith(event)))
					return false;

				auto result = onEvent(event);

				_eventHandlers.invoke(event);

				return result;
			}

			virtual bool onEvent(TouchEvent& event) {
				return false;
			}

		protected:
			virtual Size measureOverride(Display& display, const Size& availableSize) {
				return {
					0,
					0,
				};
			}

			virtual void arrangeOverride(const Bounds& bounds) {

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

			Action<TouchEvent&> _eventHandlers {};

			void setDesiredSize(const Size& value) {
				_desiredSize = value;
			}

			void setBounds(const Bounds& value) {
				_bounds = value;
			}
	};
}