#pragma once

#include "element.h"
#include "vector"
#include "ui/geometry/rectangle.h"

namespace ui {
	class Container : public Element {
		public:
			void render() override {
				for (auto child : getChildren()) {
					child.render();
				}
			}

			std::vector<Element> getChildren() {
				return children;
			}

		protected:
			void onArrange(const Rectangle& bounds) override {
				for (auto child : getChildren()) {
					child.arrange(bounds);
				}
			}

		private:
			std::vector<Element> children {};
	};
}