#pragma once

#include "color.h"
#include "vector"
#include <cmath>

class GradientStep {
	public:
		float position;
		Color color;

		GradientStep(float position, const Color& color) :
			position(position),
			color(color)
		{

		}
};

class LinearGradient {
	public:
		std::vector<GradientStep*> steps;

		~LinearGradient() {
			for (auto & step : steps)
				delete step;

			steps.clear();
		}

		Color getColor(float position) {
			if (steps.size() < 2)
				return Color::white;

			size_t fromIndex = 0;

			// |------------|---|
			//               *

			for (size_t i = 1; i < steps.size(); i++) {
				if (steps[i]->position < position) {
					fromIndex = i;
				}
				else {
					break;
				}
			}

			auto toIndex = min(fromIndex + 1, steps.size() - 1);
			auto fromStep = steps[fromIndex];
			auto toStep = steps[toIndex];
			auto spaceBetweenSteps = toStep->position - fromStep->position;
			auto positionBetweenSteps = position - fromStep->position;

			auto result = Color(fromStep->color);
			result.interpolateTo(toStep->color, positionBetweenSteps / spaceBetweenSteps);

			return result;
		}
};