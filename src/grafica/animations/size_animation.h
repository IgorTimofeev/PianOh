#pragma once

#include "animation.h"
#include <cstdint>
#include "functional"
#include "grafica/action.h"
#include "grafica/size.h"

namespace grafica {
	class SizeAnimation : public Animation {
		public:
			SizeAnimation() = default;

			SizeAnimation(const Size& from, const Size& to, uint32_t duration);

			void onTick(Element* element, double position) override;

			const Size &getFrom() const;

			void setFrom(const Size &from);

			const Size &getTo() const;

			void setTo(const Size &to);

		private:
			Size _from;
			Size _to;
	};
}