#pragma once

#include <Adafruit_NeoPixel.h>
#include <vector>

class Particle;

class Strip {
	private:
		const uint8_t R = 0xf2;
		const uint8_t G = 0xbe;
		const uint8_t B = 0x3a;
		const uint8_t AMBIENT = 0x00;

		Adafruit_NeoPixel leds;
		std::vector<Particle*> particles;

	public:
		float* pixels;

		Strip(uint16_t _length, int16_t _pin);

		~Strip();

		void addParticle(Particle* particle);

		float getPixel(int i);

		bool isIndexInRange(int index);

		void setPixel(int i, float value);

		uint16_t getLength();

		void begin();

		void render();
};