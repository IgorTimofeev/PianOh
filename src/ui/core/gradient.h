#pragma once

#include "color.h"
#include "vector"
#include <cmath>

class GradientStop {
	public:
		GradientStop(float position, const Color& color) :
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
		Color getColor(float position) {
			if (_stops.size() < 2)
				return Color::white;

			size_t fromIndex = 0;

			// |------------|---|
			//               *

			for (size_t i = 1; i < _stops.size(); i++) {
				if (_stops[i].getPosition() < position) {
					fromIndex = i;
				}
				else {
					break;
				}
			}

			auto toIndex = min(fromIndex + 1, _stops.size() - 1);
			auto fromStep = _stops[fromIndex];
			auto toStep = _stops[toIndex];
			auto spaceBetweenSteps = toStep.getPosition() - fromStep.getPosition();
			auto positionBetweenSteps = position - fromStep.getPosition();

			auto result = Color(fromStep.getColor());
			result.interpolateTo(toStep.getColor(), positionBetweenSteps / spaceBetweenSteps);

			return result;
		}

		std::vector<GradientStop>& getStops() {
			return _stops;
		}

		void addRainbowStops() {
			_stops.emplace_back(0, Color(0xFF, 0x00, 0xFF));
			_stops.emplace_back(0.2, Color(0x00, 0x00, 0xff));
			_stops.emplace_back(0.4, Color(0x00, 0xff, 0xff));
			_stops.emplace_back(0.6, Color(0x00, 0xFF, 0x00));
			_stops.emplace_back(0.8, Color(0xFF, 0xFF, 0x00));
			_stops.emplace_back(1, Color(0xFF, 0x00, 0x00));
		}

	private:
		std::vector<GradientStop> _stops {};
};