#pragma once

#include <cstdint>
#include "functional"
#include "grafica/action.h"

namespace grafica {
	class Element;

	class Animation {
		public:
			void start();

			void stop();

			void tick(Element* element, uint32_t time);

			uint32_t getDuration() const;

			void setDuration(uint32_t duration);

			bool isStarted();

			void addOnCompleted(const std::function<void()>& value);

		protected:
			virtual void onTick(Element* element, double position) = 0;

		private:
			Action<> _onCompleted;
			uint32_t _start = 0;
			uint32_t _duration = 0;
	};
}