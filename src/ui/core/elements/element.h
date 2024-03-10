#pragma once

#include <cstdint>
#include <limits>

#include "ui/core/action.h"
#include "ui/core/margin.h"
#include "ui/core/bounds.h"
#include "ui/core/size.h"

namespace ui {
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
	class TouchEvent;

	class Element {
		public:
			Element() = default;

			virtual ~Element() = default;

			Size measure(Display& display, const Size& availableSize);

			void arrange(const Bounds& bounds);

			virtual void render(Display& display);

			virtual void invalidateLayout();

			bool handleEvent(TouchEvent& event);

			virtual bool onEvent(TouchEvent& event);

			virtual void addEventHandler(const std::function<void(TouchEvent&)>& handler);

			int32_t tag = 0;

			// -------------------------------- Getters & setters --------------------------------

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

			Element* getFirstParent();
			void setFirstParent(Element* value);

			Element* getParent();
			void setParent(Element* value);

		protected:
			virtual Size onMeasure(Display& display, const Size& availableSize);

			virtual void onArrange(const Bounds& bounds);

		private:
			Size _size = Size(Size::calculated, Size::calculated);
			Alignment _horizontalAlignment = Alignment::stretch;
			Alignment _verticalAlignment = Alignment::stretch;
			Margin _margin = Margin();
			Element* _firstParent = nullptr;
			Element* _parent = nullptr;

			Bounds _bounds;
			Size _desiredSize = Size();

			Action<TouchEvent&> _eventHandlers {};

			void setDesiredSize(const Size& value);

			void setBounds(const Bounds& value);

			static void calculateArrangeShit(
				const Alignment& alignment,
				const int32_t& position,
				const uint16_t& size,
				const uint16_t& desiredSize,
				const uint16_t& marginStart,
				const uint16_t& marginEnd,
				const uint16_t& limit,
				int32_t& newPosition,
				int32_t& newSize
			);
	};
}