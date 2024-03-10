#pragma once

#include "layout.h"
#include "vector"

namespace ui {
	class Selector;

	class SelectorItem : public Layout {
		public:
			virtual void setSelected(const bool& value);

			Selector *getSelector() const;

			void setSelector(Selector *value);

		protected:
			bool onEvent(TouchEvent &event) override;

		private:
			Selector* _selector = nullptr;
	};
}