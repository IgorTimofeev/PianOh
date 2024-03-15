#pragma once

#include <cstdint>
#include <limits>

#include "grafica/action.h"
#include "grafica/margin.h"
#include "grafica/bounds.h"
#include "grafica/size.h"

namespace grafica {
	enum Alignment: uint8_t {
		start,
		center,
		end,
		stretch,
	};

	enum Orientation: uint8_t {
		horizontal,
		vertical,
	};

	class Display;
	class Event;
	class Workspace;
	class Animation;

	class Element {
		public:
			Element() = default;

			virtual ~Element() = default;

			Size measure(Display& display, const Size& availableSize);

			void arrange(const Bounds& bounds);

			virtual void tick();
			virtual void render(Display &display);
			virtual void handleEvent(Event& event);

			virtual void invalidateRender();
			virtual void invalidateLayout();
			virtual void invalidate();

			virtual void addEventHandler(const std::function<void(Event&)>& handler);

			void addAnimation(Animation* animation);

			int32_t tag = 0;

			// -------------------------------- Getters & setters --------------------------------

			bool isVisible() const;
			void setVisible(bool value);
			bool isEnabled() const;
			void setEnabled(bool value);

			Alignment getHorizontalAlignment() const;
			void setHorizontalAlignment(Alignment value);

			Alignment getVerticalAlignment() const;
			void setVerticalAlignment(Alignment value);
			void setAlignment(Alignment horizontal, Alignment vertical);
			void setAlignment(Alignment uniformValue);

			const Margin& getMargin();
			void setMargin(const Margin& value);

			const Size& getSize();
			void setSize(const Size& value);

			const Size& getDesiredSize();

			const Bounds& getBounds();

			Workspace* getWorkspace();
			void setWorkspace(Workspace* value);

			Element* getParent();
			void setParent(Element* value);

			void setCaptured(const bool &value);
			bool isCaptured();

		protected:
			virtual Size onMeasure(Display& display, const Size& availableSize);
			virtual void onArrange(const Bounds& bounds);
			virtual void onRender(Display& display);
			virtual void onEvent(Event& event);

		private:
			bool _isVisible = true;
			bool _isEnabled = true;
			Size _size = Size(Size::calculated, Size::calculated);
			Alignment _horizontalAlignment = Alignment::stretch;
			Alignment _verticalAlignment = Alignment::stretch;
			Margin _margin = Margin::zero;
			Workspace* _workspace = nullptr;
			Element* _parent = nullptr;

			Bounds _bounds;
			Size _desiredSize = Size();

			Action<Event&> _eventHandlers {};

			void setDesiredSize(const Size& value);

			void setBounds(const Bounds& value);

			static void calculateMeasureShit(
				const Alignment &alignment,
				const uint16_t &size,
				const uint16_t &desiredSize,
				const int32_t &marginStart,
				const int32_t &marginEnd,
				int32_t &newSize
			);

			static void calculateArrangeShit(
				const Alignment& alignment,
				const int32_t& position,
				const uint16_t& size,
				const uint16_t& desiredSize,
				const int32_t& marginStart,
				const int32_t& marginEnd,
				const uint16_t& limit,
				int32_t& newPosition,
				int32_t& newSize
			);
	};
}