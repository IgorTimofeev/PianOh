#pragma once

#include "element.h"
#include "grafica/bounds.h"
#include "vector"

namespace grafica {
	class Layout : public Element {
		public:
			void tick() override;

			void render(Display& display) override;

			void onEvent(Event& event) override;

			std::vector<Element*>::iterator begin();

			std::vector<Element*>::iterator end();

			size_t getChildrenCount();

			int32_t getIndexOfChild(Element* element);

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