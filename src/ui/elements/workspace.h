#pragma once

#include "layout.h"
#include "ui/event.h"

namespace ui {
	class Workspace : public Layout {
		public:
			Workspace() {
				setFirstParent(this);
			}

			void measure(Display& display)  {
				if (isMeasured)
					return;

				Layout::measure(display, getSize());
				isMeasured = true;
			}

			void arrange() {
				if (isArranged)
					return;

				Layout::arrange(Bounds(getSize()));
				isArranged = true;
			}

			void render(Display& display) override {
				if (isRendered)
					return;

				Layout::render(display);
				isRendered = true;
			}

			void invalidateLayout() override {
				isMeasured = false;
				isArranged = false;
				isRendered = false;
			}

		private:
			bool isRendered = false;
			bool isMeasured = false;
			bool isArranged = false;
	};
}