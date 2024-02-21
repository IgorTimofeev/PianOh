#include "strip/strip.h"
#include "strip/particles/particle.h"
#include "strip/fillers/color_filler.h"
#include "color.h"

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

bool Strip::revertIndexIfRequired(uint16_t& index) {
	if (isReversed)
		index = getLength() - index - 1;
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
	if (!isIndexInRange(index))
		return Color();

	revertIndexIfRequired(index);

	return Color(leds.getPixelColor(index));
}

void Strip::setColor(uint16_t index, const Color& value) {
	if (!isIndexInRange(index))
		return;

	revertIndexIfRequired(index);

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
	if (filler) {
		filler->render(*this);
	}
	else {
		clear();
	}

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

void Strip::clear() {
	leds.clear();
}

void Strip::fill(uint16_t from, uint16_t to, Color color) {
	revertIndexIfRequired(from);
	revertIndexIfRequired(to);

	leds.fill(from, to, color.toUint32());
}

void Strip::fill(const Color& color) {
	fill(0, getLength() - 1, color);
}