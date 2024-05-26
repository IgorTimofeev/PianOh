#include <Arduino.h>
#include "ui/piano_application.h"

using namespace ui;

PianoApplication& application = PianoApplication::getInstance();

void setup() {
	Serial.begin(115200);

	application.begin();
}

void loop() {
	application.tick();
}