#pragma once

#include "layout.h"

namespace ui {
	class StackLayout : public Layout {
		public:
			Orientation getOrientation() const {
				return _orientation;
			}

			void setOrientation(Orientation orientation) {
				_orientation = orientation;
			}

			int32_t getSpacing() const {
				return _spacing;
			}

			void setSpacing(int32_t value) {
				_spacing = value;
			}

		protected:
			Size onMeasure(Display& display, const Size& availableSize) override {
				auto result = Size();

				Size childSize;

				switch (getOrientation()) {
					case horizontal:
						for (auto child : *this) {
							childSize = child->measure(
								display,
								Size(
									Size::infinity,
									availableSize.getHeight()
								)
							);

							result.setWidth(result.getWidth() + childSize.getWidth() + getSpacing());

							if (childSize.getHeight() > result.getHeight())
								result.setHeight(childSize.getHeight());
						}

						if (getChildrenCount() > 0)
							result.setWidth(result.getWidth() - getSpacing());

						break;

					case vertical:
						for (auto child : *this) {
							childSize = child->measure(
								display,
								Size(
									availableSize.getWidth(),
									Size::infinity
								)
							);

							if (childSize.getWidth() > result.getWidth())
								result.setWidth(childSize.getWidth());

							result.setHeight(result.getHeight() + childSize.getHeight() + getSpacing());
						}

						if (getChildrenCount() > 0)
							result.setHeight(result.getHeight() - getSpacing());

						break;
				}

				return result;
			}

			void onArrange(const Bounds& bounds) override {
				int32_t position;

				switch (getOrientation()) {
					case horizontal:
						position = bounds.getX();

						for (auto child : *this) {
							child->arrange(Bounds(
								position,
								bounds.getY(),
								child->getDesiredSize().getWidth(),
								bounds.getHeight()
							));

							position += child->getDesiredSize().getWidth() + getSpacing();
						}

						break;

					case vertical:
						position = bounds.getY();

						for (auto child : *this) {
							child->arrange(Bounds(
								bounds.getX(),
								position,
								bounds.getWidth(),
								child->getDesiredSize().getHeight()
							));

							position += child->getDesiredSize().getHeight() + getSpacing();
						}

						break;
				}
			}

		private:
			int32_t _spacing = 10;
			Orientation _orientation = Orientation::vertical;
	};
}