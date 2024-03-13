#pragma once

#include "element.h"
#include "grafica/display.h"
#include "grafica/bounds.h"
#include "grafica/image_source.h"

namespace grafica {
	class Image : public Element {
		public:
			void render(Display& display) override {
				if (!getSource() || !getSource()->getPixels())
					return;

				display.drawImage(
					Bounds(
						getBounds().getPosition(),
						getSource()->getSize()
					),
					getSource()->getPixels()
				);
			}

			// -------------------------------- Getters & setters --------------------------------

			const ImageSource* getSource() const {
				return _source;
			}

			void setSource(ImageSource* source) {
				_source = source;

				invalidate();
			}

		private:
			ImageSource* _source = nullptr;
	};
}
