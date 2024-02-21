#pragma once

class Strip;

class Particle {
	public:
		float position = 0;
		float life = 1;

		Particle() = default;
		virtual ~Particle() = default;

		virtual void render(Strip& strip) = 0;
};