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
				// Selection
				addChild(&_selectionBackground);

				_selectionLine.setSize(Size(3, Size::calculated));
				_selectionLine.setHorizontalAlignment(Alignment::start);
				addChild(&_selectionLine);

				// Row
				_row.setSpacing(10);
				_row.setMargin(Margin(8, 5, 5, 5));
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
				_selectionBackground.setVisible(value);
				_selectionLine.setVisible(value);

				_text.setForeground(value ? Color::alt1 : Color::alt7);

				_image.setSource(value ? _imageSourceOn : _imageSourceOff);
			}

		private:
			Rectangle _selectionBackground = Rectangle(Color::main3);
			Rectangle _selectionLine = Rectangle(Color::gold);

			StackLayout _row = StackLayout();

			Image _image = Image();
			ImageSource *_imageSourceOn;
			ImageSource *_imageSourceOff;
			Text _text = Text();
	};
}