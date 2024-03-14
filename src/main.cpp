#include <Arduino.h>
#include "ui/application.h"

#define LED_ONBOARD_PIN1 12
#define LED_ONBOARD_PIN2 13

using namespace ui;

Application& application = Application::getInstance();

void setup() {
	// Onboard LED
	pinMode(LED_ONBOARD_PIN1, OUTPUT);
	pinMode(LED_ONBOARD_PIN2, OUTPUT);
	digitalWrite(LED_ONBOARD_PIN1, HIGH);

	application.begin();
}

void loop() {
	application.loop();
}