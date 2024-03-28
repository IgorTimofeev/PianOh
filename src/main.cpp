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

//#include <Arduino.h>
//#include "TFT_eSPI.h"
//
//TFT_eSPI tft = TFT_eSPI();
//TFT_eSprite buffer = TFT_eSprite(&tft);
//
//void setup() {
//	Serial.begin(115200);
//
//	tft.init();
//	tft.setRotation(1);
//
//	buffer.setAttribute(PSRAM_ENABLE, true);
//	buffer.createSprite(TFT_HEIGHT, TFT_WIDTH);
//}
//
//void loop() {
//	buffer.fillSprite(random(0xFFFF));
//
//	// Draw some random circles
//	for (int i = 0; i < 40; i++)
//	{
//		int radius = random(60);
//		int x = random(TFT_HEIGHT) - radius  /2;
//		int y = random(TFT_WIDTH) - radius / 2;
//		buffer.fillEllipse(x, y, radius, radius, random(0xFFFF));
//	}
//
//	buffer.pushSprite(0, 0);
//	delay(1000);
//}