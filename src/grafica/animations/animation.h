#pragma once

#include <cstdint>
#include "functional"
#include "grafica/action.h"

namespace grafica {
	class Element;

	template<typename T>
	class Animation {
		public:
			Animation() = default;

			Animation(
				T from,
				T to,
				const uint32_t &duration
			) {
				setFrom(from);
				setTo(to);
				setDuration(duration);
			}

			void start();

			void stop();

			bool tick();

			uint32_t getDuration() const;

			void setDuration(const uint32_t &duration);

			bool isStarted() const;

			void addOnCompleted(const std::function<void()>& value);

			T getFrom() const;

			void setFrom(T from);

			T getTo() const;

			void setTo(T to);

		protected:
			virtual T interpolate(const double& position) = 0;

		private:
			T _from;
			T _to;
			Action<double> _onTick;
			Action<> _onCompleted;
			uint32_t _start = 0;
			uint32_t _duration = 0;
	};
}