#pragma once

#include "element.h"
#include "vector"
#include "screen/ui/geometry/bounds.h"

namespace ui {
	class Container : public Element {
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
			void onArrange(const Bounds& bounds) override {
				for (auto child : getChildren()) {
					child->arrange(bounds);
				}
			}

		private:
			std::vector<Element*> children {};
	};
}