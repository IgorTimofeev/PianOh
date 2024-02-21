#pragma once

#include "Adafruit_NeoPixel.h"
#include <vector>
#include "color.h"

class Particle;

class Strip {
	private:
		Adafruit_NeoPixel leds;
		std::vector<Particle*> particles;

	public:
		Strip(uint16_t _length, int16_t _pin);

		~Strip();

		void addParticle(Particle* particle);
		void removeParticleAt(uint16_t index);

		uint16_t getLength();

		bool isIndexInRange(uint16_t index);

		uint8_t getBrightness();
		void setBrightness(uint8_t value);

		Color getColor(uint16_t index);
		void setColor(uint16_t index, const Color& value);

		void begin();

		void render();
};