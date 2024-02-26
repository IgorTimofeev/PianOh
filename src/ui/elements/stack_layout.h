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
			Size onMeasure(const Size& constraint) override {
				auto result = Size();

				Size childSize;

				switch (getOrientation()) {
					case Horizontal:
						for (auto child : getChildren()) {
							childSize = child->measure(Size(
								Size::infinity,
								constraint.getHeight()
							));

							result.setWidth(result.getWidth() + childSize.getWidth() + getSpacing());

							if (childSize.getHeight() > result.getHeight())
								result.setHeight(childSize.getHeight());
						}

						if (!getChildren().empty())
							result.setWidth(result.getWidth() - getSpacing());

						break;

					case Vertical:
						for (auto child : getChildren()) {
							childSize = child->measure(Size(
								constraint.getWidth(),
								Size::infinity
							));

							if (childSize.getWidth() > result.getWidth())
								result.setWidth(childSize.getWidth());

							result.setHeight(result.getHeight() + childSize.getHeight() + getSpacing());
						}

						if (getChildren().empty())
							result.setHeight(result.getHeight() - getSpacing());

						break;
				}

				return result;
			}

			void onArrange(const Bounds& bounds) override {
				int32_t position;

				switch (getOrientation()) {
					case Horizontal:
						position = bounds.point.getX();

						for (auto child : getChildren()) {
							child->arrange(Bounds(
								position,
								bounds.point.getY(),
								child->getDesiredSize().getWidth(),
								bounds._size.getHeight()
							));

							position += child->getDesiredSize().getWidth() + getSpacing();
						}

						break;

					case Vertical:
						position = bounds.point.getY();

						for (auto child : getChildren()) {
							child->arrange(Bounds(
								bounds.point.getX(),
								position,
								bounds._size.getWidth(),
								child->getDesiredSize().getHeight()
							));

							position += child->getDesiredSize().getHeight() + getSpacing();
						}

						break;
				}
			}

		private:
			int32_t _spacing = 10;
			Orientation _orientation = Orientation::Vertical;
	};
}