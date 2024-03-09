#pragma once

#include "element.h"
#include "ui/display.h"
#include "ui/bounds.h"
#include "ui/image_source.h"

namespace ui {
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

				invalidateLayout();
			}

		private:
			ImageSource* _source = nullptr;
	};
}
