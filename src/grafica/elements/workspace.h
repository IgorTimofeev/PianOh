#pragma once

#include "layout.h"
#include "grafica/event.h"

namespace grafica {
	class Display;
	class Animation;

	class Workspace : public Layout {
		public:
			Workspace();

			void measure(Display& display);
			void arrange();
			void render(Display& display) override;
			void invalidateLayout() override;
			void invalidateRender() override;
			void invalidate() override;
			void tick() override;

			void addAnimation(Element* element, Animation* animation);

		private:
			bool _isRendered = false;
			bool _isMeasured = false;
			bool _isArranged = false;
			std::vector<std::pair<Element*, Animation*>> _animations {};

			void animate();
	};
}