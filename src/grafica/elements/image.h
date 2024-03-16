#pragma once

#include "element.h"
#include "grafica/screen.h"
#include "grafica/bounds.h"
#include "grafica/image_source.h"

namespace grafica {
	class Image : public Element {
		public:
			void onRender(Screen& display) override {
				if (!getSource() || !getSource()->getPixels())
					return;

				display.renderImage(
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
