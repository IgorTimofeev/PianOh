#pragma once

#include "Arduino.h"
#include "ui/elements/layout.h"
#include "ui/elements/tab_bar.h"
#include "ui/elements/image.h"

#include "resources/images/gradient.h"
#include "resources/images/flame.h"
#include "resources/images/wave.h"
#include "resources/images/strobe.h"
#include "ui/elements/linear_gradient_view.h"

using namespace ui;

class TabItemView : public SelectorItem {
	public:
		TabItemView(uint16_t* pixelsOn, uint16_t* pixelsOff) :
			_pixelsOn(pixelsOn),
			_pixelsOff(pixelsOff),
			_imageSource(ImageSource(Size(40, 40), pixelsOn))
		{
			// Background rect
			addChild(&_rectangle);

			// Image
			_image.setSize(Size(40, 40));
			_image.setMargin(Margin(10));
			_image.setSource(&_imageSource);
			addChild(&_image);
		}

		void setSelected(const bool &value) override {
			_rectangle.setFillColor(value ? Color::white : Color::black);
			_imageSource.setPixels(value ? _pixelsOn : _pixelsOff);
			_image.invalidateLayout();
		}

	private:
		Rectangle _rectangle = Rectangle(Color::white);
		Image _image = Image();
		ImageSource _imageSource;

		uint16_t* _pixelsOn;
		uint16_t* _pixelsOff;
};

class TabView1 : public StackLayout {
	public:
		TabView1() {
			setAlignment(Alignment::center);

			gradientView.setSize(Size(300, 50));
			gradientView.setMargin(Margin(20));
			addChild(&gradientView);
		}

		LinearGradientView gradientView = LinearGradientView();
};

class TabView2 : public StackLayout {
	public:
		TabView2() {
			setAlignment(Alignment::center);

			// Slider
			slider.setCornerRadius(5);
			slider.setValue(0.7);
			slider.setSize(Size(150, 40));

			addChild(&slider);

			// Text
			text.setText("Initial text");
			addChild(&text);

			slider.addOnValueChanged([this]() {
				text.setText(String("Value: ") + slider.getValue());
			});
		}

		Slider slider = Slider();
		Text text = Text();
};

class TabView3 : public Layout {
	public:
		SevenSegment sevenSegment = SevenSegment();

		TabView3() {
			setAlignment(Alignment::center);

			// SevenSegment
			sevenSegment.setSegmentThickness(3);
			sevenSegment.setSegmentLength(9);
			sevenSegment.setSpacing(3);
			sevenSegment.setDigitCount(6);
			sevenSegment.setHorizontalAlignment(Alignment::center);

			sevenSegment.addEventHandler([this](TouchEvent& event) {
				if (event.getType() == TouchEventType::Touch) {
					sevenSegment.setValue(sevenSegment.getValue() + 1);
				}
			});

			addChild(&sevenSegment);
		}
};

class TabView4 : public Layout {
	public:
		TabView4() {
			setAlignment(Alignment::center);

			addChild(&rectangle);

			text.setAlignment(Alignment::center, Alignment::center);
			text.setMargin(Margin(10));
			text.setColor(Color::black);
			text.setText("Timer");
			addChild(&text);
		}

		Rectangle rectangle = Rectangle(Color::gold);
		Text text = Text();
};

class PianoTabBar : public TabBar {
	public:
		TabItemView tabItemView1 = TabItemView((uint16_t*) GRADIENT_ON, (uint16_t*) GRADIENT_OFF);
		TabView1 tabView1 = TabView1();

		TabItemView tabItemView2 = TabItemView((uint16_t*) WAVE_ON, (uint16_t*) WAVE_OFF);
		TabView2 tabView2 = TabView2();

		TabItemView tabItemView3 = TabItemView((uint16_t*) FLAME_ON, (uint16_t*) FLAME_OFF);
		TabView3 tabView3 = TabView3();

		TabItemView tabItemView4 = TabItemView((uint16_t*) STROBE_ON, (uint16_t*) STROBE_OFF);
		TabView4 tabView4 = TabView4();

		PianoTabBar() {
			this->addTabAndView(&tabItemView1, &tabView1);
			this->addTabAndView(&tabItemView2, &tabView2);
			this->addTabAndView(&tabItemView3, &tabView3);
			this->addTabAndView(&tabItemView4, &tabView4);
			this->setSelectedIndex(0);
		}
};