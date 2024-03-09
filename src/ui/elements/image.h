#pragma once

#include "element.h"
#include "ui/display.h"
#include "ui/bounds.h"

namespace ui {
	class Image : public Element {
		public:
			void render(Display& display) override {
				if (getPixels())
					display.drawImage(getBounds(), getPixels());
			}

			// -------------------------------- Getters & setters --------------------------------

			uint16_t *getPixels() const {
				return pixels;
			}

			void setPixels(uint16_t *value) {
				Image::pixels = value;
			}

		private:
			uint16_t* pixels = nullptr;
	};
}
