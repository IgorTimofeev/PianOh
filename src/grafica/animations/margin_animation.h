#pragma once

#include "animation.h"
#include <cstdint>
#include "functional"
#include "grafica/action.h"
#include "grafica/margin.h"

namespace grafica {
	class MarginAnimation : public Animation {
		public:
			MarginAnimation() = default;

			MarginAnimation(const Margin& from, const Margin& to, uint32_t duration);

			void onTick(Element* element, double position) override;

			const Margin &getFrom() const;

			void setFrom(const Margin &from);

			const Margin &getTo() const;

			void setTo(const Margin &to);

		private:
			Margin _from;
			Margin _to;
	};
}