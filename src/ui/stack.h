#pragma once

#include "ui/container.h"

namespace ui {
	class Stack : public Container {
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
			void onArrange(const Rectangle& bounds) override {
				int32_t x = bounds.point.getX();
				int32_t y = bounds.point.getY();

				switch (getOrientation()) {
					case Horizontal:
						for (auto child : getChildren()) {
							child.arrange(Rectangle(
								x,
								y,
								bounds.size.getWidth(),
								child.getCalculatedSize().getHeight()
							));
						}

						x += getSpacing();

						break;

					case Vertical:
						for (auto child : getChildren()) {
							child.arrange(Rectangle(
								x,
								y,
								child.getCalculatedSize().getWidth(),
								bounds.size.getHeight()
							));
						}

						y += getSpacing();

						break;
				}
			}

		private:
			int32_t _spacing = 0;
			Orientation _orientation = Orientation::Vertical;
	};
}