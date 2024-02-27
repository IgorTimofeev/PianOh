#pragma once

#include "element.h"
#include "vector"
#include "ui/geometry/bounds.h"

namespace ui {
	class Layout : public Element {
		public:
			void render(Display& display) override {
				for (auto child : *this) {
					child->setParent(this);
					child->setFirstParent(getFirstParent());
					child->render(display);
				}
			}

			std::vector<Element*>::iterator begin() {
				return _children.begin();
			}

			std::vector<Element*>::iterator end() {
				return _children.end();
			}

			size_t getChildrenCount() {
				return _children.size();
			}

			int getIndexOfChild(Element* element) {
				auto iterator = find(_children.begin(), _children.end(), element);

				if (iterator == _children.end()) {
					return -1;
				}
				else {
					return iterator - _children.begin();
				}
			}

			void removeChildAt(int index) {
				auto element = _children[index];

				_children.erase(_children.begin() + index);

				invalidateLayout();
			}

			void removeChild(Element* child) {
				auto iterator = std::find(_children.begin(), _children.end(), child);

				if (iterator == _children.end())
					return;

				_children.erase(iterator);

				invalidateLayout();
			}

			void removeChildren() {
				_children.clear();

				invalidateLayout();
			}

			Element* getChildAt(int index) {
				return _children[index];
			}

			void addChild(Element* child) {
				child->setParent(this);
				child->setFirstParent(getFirstParent());

				_children.push_back(child);

				invalidateLayout();
			}

			virtual Element* operator[](int index) {
				return getChildAt(index);
			}

			virtual void operator+=(Element* child) {
				addChild(child);
			}

			virtual void operator-=(Element* child) {
				removeChild(child);
			}

		protected:
			Size onMeasure(Display& display, const Size& availableSize) override {
				auto result = Size();

				Size childSize;

				for (auto child : *this) {
					childSize = child->measure(display, availableSize);

					if (childSize.getWidth() > result.getWidth())
						result.setWidth(childSize.getWidth());

					if (childSize.getHeight() > result.getHeight())
						result.setHeight(childSize.getHeight());
				}

				return result;
			}

			void onArrange(const Bounds& bounds) override {
				for (auto child : *this) {
					child->arrange(bounds);
				}
			}

		private:
			std::vector<Element*> _children {};
	};
}