#pragma once

#include "layout.h"
#include "vector"

namespace grafica {
	class Selector;

	class SelectorItem : public Layout {
		public:
			virtual void setSelected(const bool& value);

			Selector *getSelector() const;

			void setSelector(Selector *value);

		protected:
			bool onEvent(Event &event) override;

		private:
			Selector* _selector = nullptr;
	};
}