#pragma once

#include "ui/color.h"
#include "vector"
#include <cmath>

class GradientStep {
	public:
		GradientStep(float position, const Color& color) :
			_position(position),
			_color(color)
		{

		}

		float getPosition() const {
			return _position;
		}

		void setPosition(float value) {
			_position = value;
		}

		Color& getColor() {
			return _color;
		}

		void setColor(Color& value) {
			_color = value;
		}

	private:
		float _position;
		Color _color;
};

class LinearGradient {
	public:
		explicit LinearGradient(const std::vector<GradientStep*>& steps) {
			setSteps(steps);
		}

		~LinearGradient() {
			for (auto& step : _steps) {
				delete step;
			}
		}

		Color getColor(float position) {
			if (_steps.size() < 2)
				return Color::white;

			size_t fromIndex = 0;

			// |------------|---|
			//               *

			for (size_t i = 1; i < _steps.size(); i++) {
				if (_steps[i]->getPosition() < position) {
					fromIndex = i;
				}
				else {
					break;
				}
			}

			auto toIndex = min(fromIndex + 1, _steps.size() - 1);
			auto fromStep = _steps[fromIndex];
			auto toStep = _steps[toIndex];
			auto spaceBetweenSteps = toStep->getPosition() - fromStep->getPosition();
			auto positionBetweenSteps = position - fromStep->getPosition();

			auto result = Color(fromStep->getColor());
			result.interpolateTo(toStep->getColor(), positionBetweenSteps / spaceBetweenSteps);

			return result;
		}

		std::vector<GradientStep*>& getSteps() {
			return _steps;
		}

		void setSteps(const std::vector<GradientStep*>& steps) {
			_steps = steps;
		}

	private:
		std::vector<GradientStep*> _steps;
};