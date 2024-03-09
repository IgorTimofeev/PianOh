#pragma once

#include "layout.h"
#include "vector"

namespace ui {
	class ItemsHost;

	class ItemsHostItem : public Layout {
		public:
			virtual void setSelected(const bool& value);

			ItemsHost *getItemsHost() const;

			void setItemsHost(ItemsHost *itemsHost);

		protected:
			bool onEvent(TouchEvent &event) override;

		private:
			ItemsHost* _itemsHost = nullptr;
	};
}