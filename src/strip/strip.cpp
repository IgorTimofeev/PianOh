#include "strip.h"
#include "color.h"
#include "particles/particle.h"

Strip::Strip(uint16_t _length, int16_t _pin) {
	leds = Adafruit_NeoPixel(_length, _pin, NEO_GRB + NEO_KHZ800);
}

Strip::~Strip() {
	for (auto particle : particles) {
		delete particle;
	}
}

uint16_t Strip::getLength() {
	return leds.numPixels();
}

bool Strip::isIndexInRange(uint16_t index) {
	return index >= 0 && index < getLength();
}

uint8_t Strip::getBrightness() {
	return leds.getBrightness();
}

void Strip::setBrightness(uint8_t value) {
	leds.setBrightness(value);
}

Color Strip::getColor(uint16_t index) {
	return isIndexInRange(index) ? Color(leds.getPixelColor(index)) : Color();
}

void Strip::setColor(uint16_t index, const Color& value) {
	if (!isIndexInRange(index))
		return;

	leds.setPixelColor(index, value.r, value.g, value.b);
}

void Strip::addParticle(Particle* particle) {
	particles.push_back(particle);
}

void Strip::removeParticleAt(uint16_t index) {
	auto particle = particles[index];
	particles.erase(particles.begin() + index);
	delete particle;
}

void Strip::begin() {
	leds.begin();
}

void Strip::render() {
	for (int i = 0; i < getLength(); i++)
		setColor(i, Color());

	Particle* particle;

	for (int i = 0; i < particles.size(); i++) {
		particle = particles[i];

		particle->render(*this);

		if (particle->life <= 0) {
			removeParticleAt(i);
			i--;
		}
	}

	leds.show();
}