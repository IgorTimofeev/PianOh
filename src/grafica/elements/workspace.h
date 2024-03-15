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
			void onRender(Display& display) override;
			void invalidateLayout() override;
			void invalidateRender() override;
			void invalidate() override;
			void tick() override;

			void addAnimation(Element* element, Animation* animation);

			Element *getCapturedElement() const;

			void setCapturedElement(Element *capturedElement);

			void handleEvent(Event &event) override;

		private:
			bool _isRendered = false;
			bool _isMeasured = false;
			bool _isArranged = false;
			Element* _capturedElement = nullptr;
			std::vector<std::pair<Element*, Animation*>> _animations {};

			void animate();
	};
}