#pragma once

#include "Arduino.h"
#include "grafica/color.h"
#include "grafica/image_source.h"
#include "grafica/elements/selector.h"
#include "grafica/elements/rectangle.h"
#include "grafica/elements/image.h"

using namespace grafica;

namespace ui {
	class TabItemView : public SelectorItem {
		public:
			TabItemView(ImageSource *imageSourceOn, ImageSource *imageSourceOff) :
				_imageSourceOn(imageSourceOn),
				_imageSourceOff(imageSourceOff) {
				// Background rect
				addChild(&_rectangle);

				// Image
				_image.setMargin(Margin(10));
				_image.setSource(_imageSourceOn);
				_image.setSize(imageSourceOn->getSize());
				addChild(&_image);
			}

			void setSelected(const bool &value) override {
				_rectangle.setFillColor(value ? Color::white : Color::black);
				_image.setSource(value ? _imageSourceOn : _imageSourceOff);
			}

		private:
			Rectangle _rectangle = Rectangle(Color::white);
			Image _image = Image();
			ImageSource *_imageSourceOn;
			ImageSource *_imageSourceOff;
	};
}