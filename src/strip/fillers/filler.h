#pragma once

class Strip;

class Filler {
	public:
		Filler() = default;

		virtual ~Filler() = default;

		virtual void render(Strip& strip) = 0;
};