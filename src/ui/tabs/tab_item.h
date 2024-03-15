#pragma once

#include "Arduino.h"
#include "grafica/color.h"
#include "grafica/image_source.h"
#include "grafica/elements/selector_item.h"
#include "grafica/elements/rectangle.h"
#include "grafica/elements/image.h"
#include "grafica/elements/text.h"
#include "grafica/elements/stack_layout.h"

using namespace grafica;

namespace ui {
	class TabItem : public SelectorItem {
		public:
			TabItem(ImageSource *imageSourceOn, ImageSource *imageSourceOff, const String& text) :
				_imageSourceOn(imageSourceOn),
				_imageSourceOff(imageSourceOff)
			{
				// Background rect
				_rectangle.setCornerRadius(4);
				addChild(&_rectangle);

				// Row
				_row.setMargin(Margin(5));
				_row.setVerticalAlignment(Alignment::center);
				_row.setOrientation(Orientation::horizontal);
				addChild(&_row);

				// Image
				_image.setSize(imageSourceOn->getSize());
				_image.setVerticalAlignment(Alignment::center);
				_row.addChild(&_image);

				// Text
				_text.setVerticalAlignment(Alignment::center);
				_text.setText(text);
				_row.addChild(&_text);

				setSelected(false);
			}

			void setSelected(const bool &value) override {
				_rectangle.setFillColor(value ? Color::white : Color::black);
				_image.setSource(value ? _imageSourceOn : _imageSourceOff);
				_text.setForeground(value ? Color::black : Color::gray);
			}

		private:
			Rectangle _rectangle = Rectangle(Color::white);
			StackLayout _row = StackLayout();

			Image _image = Image();
			ImageSource *_imageSourceOn;
			ImageSource *_imageSourceOff;
			Text _text = Text();
	};
}