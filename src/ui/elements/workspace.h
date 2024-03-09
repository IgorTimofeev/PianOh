#pragma once

#include "layout.h"
#include "ui/event.h"

namespace ui {
	class Display;

	class Workspace : public Layout {
		public:
			Workspace();

			void measure(Display& display);

			void arrange();

			void render(Display& display) override;

			void invalidateLayout() override;

		private:
			bool _isRendered = false;
			bool _isMeasured = false;
			bool _isArranged = false;
	};
}