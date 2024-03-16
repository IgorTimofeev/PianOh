#pragma once

#include "animation.h"
#include <cstdint>
#include "functional"
#include "grafica/action.h"
#include "grafica/margin.h"

namespace grafica {
	class MarginAnimation : public Animation<Margin> {
		public:
			MarginAnimation();
			MarginAnimation(const Margin &from, const Margin &to, const uint32_t &duration);

		protected:
			Margin interpolate(const double &position) override;
	};
}