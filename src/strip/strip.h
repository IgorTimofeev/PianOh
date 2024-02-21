#pragma once

#include "Adafruit_NeoPixel.h"
#include <vector>
#include "color.h"
#include "strip/fillers/filler.h"

class Filler;
class Particle;

class Strip {
	private:
		Adafruit_NeoPixel leds;
		std::vector<Particle*> particles;

		bool revertIndexIfRequired(uint16_t& index);

	public:
		Filler* filler = nullptr;
		bool isReversed = false;

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

		void clear();

		void fill(uint16_t from, uint16_t to, Color color);

		void fill(const Color& color);
};