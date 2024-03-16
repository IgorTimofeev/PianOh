#pragma once

#include "animation.h"
#include <cstdint>
#include "functional"
#include "grafica/action.h"
#include "grafica/size.h"

namespace grafica {
	class SizeAnimation : public Animation<Size> {
		public:
			SizeAnimation();

			SizeAnimation(const Size &from, const Size &to, const uint32_t &duration);

		protected:
			Size interpolate(const double &position) override;
	};
}