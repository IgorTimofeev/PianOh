#include <Arduino.h>
#include "ui/piano_application.h"

using namespace ui;

PianoApplication& application = PianoApplication::getInstance();

void setup() {
	application.begin();
}

void loop() {
	application.tick();
}