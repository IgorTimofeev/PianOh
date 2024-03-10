#pragma once

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "FT6336U.h"

#include "size.h"
#include "bounds.h"
#include "color.h"
#include "grafica/elements/workspace.h"

namespace grafica {
	class Display {
		public:
			void render();

			virtual void clear() = 0;

			virtual void begin() = 0;
			virtual void drawText(const Point& position, const Color& color, const String& text, const uint8_t& size) = 0;
			virtual void drawCircle(const Point& position, int32_t radius, const Color& color) = 0;
			virtual void drawRectangle(const Bounds& bounds, const Color& color) = 0;
			virtual void drawRectangle(const Bounds& bounds, uint16_t radius, const Color& color) = 0;
			virtual void drawFastHLine(const Point& position, uint16_t size, const Color& color) = 0;
			virtual void drawFastVLine(const Point& position, uint16_t size, const Color& color) = 0;
			virtual void drawImage(const Bounds& bounds, const uint16_t* data) = 0;
			virtual void flush() = 0;

			virtual Size measureText(const String& text, const uint8_t& fontSize) = 0;

			// -------------------------------- Getters & setters --------------------------------

			Workspace& getWorkspace();

		private:
			Workspace _workspace;
	};
}
