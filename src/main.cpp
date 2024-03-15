#include <Arduino.h>
#include "ui/application.h"

using namespace ui;

Application& application = Application::getInstance();

void setup() {
	application.begin();
}

void loop() {
	application.loop();
}