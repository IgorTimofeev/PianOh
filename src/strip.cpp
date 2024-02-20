#include "strip.h"
#include "particles/particle.h"
#include "number.h"

Strip::Strip(uint16_t _length, int16_t _pin) {
	leds = Adafruit_NeoPixel(_length, _pin, NEO_GRB + NEO_KHZ800);
	pixels = new float[_length];
}

Strip::~Strip() {
	for (auto particle : particles) {
		delete particle;
	}

	delete pixels;
}

bool Strip::isIndexInRange(int index) {
	return index >= 0 && index < getLength();
}

float Strip::getPixel(int index) {
	return isIndexInRange(index) ? pixels[index] : 0;
}

void Strip::setPixel(int index, float value) {
	if (!isIndexInRange(index))
		return;

	pixels[index] = value;
}

uint16_t Strip::getLength() {
	return leds.numPixels();
}

void Strip::addParticle(Particle* particle) {
	particles.push_back(particle);
}

void Strip::begin() {
	leds.begin();
}

void Strip::render() {
	for (int i = 0; i < getLength(); i++)
		setPixel(i, AMBIENT);

	Particle* particle;

	for (int i = 0; i < particles.size(); i++) {
		particle = particles[i];

		particle->render(*this);

		if (particle->life <= 0) {
			particles.erase(particles.begin() + i);
			delete particle;

			i--;
		}
	}

	float value;

	for (int i = 0; i < getLength(); i++) {
		value = pixels[i];

		leds.setPixelColor(
			i,
			(uint8_t) (value * R),
			(uint8_t) (value * G),
			(uint8_t) (value * B)
		);
	}

	leds.show();
}