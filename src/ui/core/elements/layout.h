#pragma once

#include "element.h"
#include "ui/core/bounds.h"
#include "vector"

namespace ui {
	class Layout : public Element {
		public:
			void render(Display& display) override;

			bool onEvent(TouchEvent& event) override;

			std::vector<Element*>::iterator begin();

			std::vector<Element*>::iterator end();

			size_t getChildrenCount();

			size_t getIndexOfChild(Element* element);

			void removeChildAt(int index);

			void removeChild(Element* child);

			void removeChildren();

			Element* getChildAt(size_t index);

			void addChild(Element* child);

			virtual Element* operator[](size_t index);

			virtual void operator+=(Element* child);

			virtual void operator-=(Element* child);

		protected:
			Size onMeasure(Display& display, const Size& availableSize) override;

			void onArrange(const Bounds& bounds) override;

		private:
			std::vector<Element*> _children {};
	};
}