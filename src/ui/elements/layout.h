#pragma once

#include "element.h"
#include "vector"
#include "ui/geometry/bounds.h"

namespace ui {
	class Layout : public Element {
		public:
			void render(Display& display) override {
				for (auto child : getChildren()) {
					child->render(display);
				}
			}

			std::vector<Element*>& getChildren() {
				return children;
			}

		protected:
			Size onMeasure(Display& display, const Size& constraint) override {
				auto result = Size();

				Size childSize;

				for (auto child : getChildren()) {
					child->setFirstParent(getFirstParent());

					childSize = child->measure(display, constraint);

					if (childSize.getWidth() > result.getWidth())
						result.setWidth(childSize.getWidth());

					if (childSize.getHeight() > result.getHeight())
						result.setHeight(childSize.getHeight());
				}

				return result;
			}

			void onArrange(const Bounds& bounds) override {
				for (auto child : getChildren()) {
					child->arrange(bounds);
				}
			}

		private:
			std::vector<Element*> children {};
	};
}