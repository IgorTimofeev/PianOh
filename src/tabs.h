#pragma once

#include "Arduino.h"
#include "ui/elements/layout.h"
#include "ui/elements/tab_bar.h"
#include "ui/elements/image.h"
#include "resources/images.h"
#include "ui/elements/linear_gradient_view.h"

using namespace ui;
using namespace resources::images;

class TabItemView : public SelectorItem {
	public:
		TabItemView(ImageSource* imageSourceOn, ImageSource* imageSourceOff) :
			_imageSourceOn(imageSourceOn),
			_imageSourceOff(imageSourceOff)
		{
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
		ImageSource* _imageSourceOn;
		ImageSource* _imageSourceOff;
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

class TabView5 : public Layout {
	public:
		TabView5() {
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
		TabItemView tabItemView1 = TabItemView(&gradientOn, &gradientOff);
		TabView1 tabView1 = TabView1();

		TabItemView tabItemView2 = TabItemView(&waveOn, &waveOff);
		TabView2 tabView2 = TabView2();

		TabItemView tabItemView3 = TabItemView(&flameOn, &flameOff);
		TabView3 tabView3 = TabView3();

		TabItemView tabItemView4 = TabItemView(&strobeOn, &strobeOff);
		TabView4 tabView4 = TabView4();

		TabItemView tabItemView5 = TabItemView(&pianoOn, &pianoOff);
		TabView5 tabView5 = TabView5();

		PianoTabBar() {
			this->addTabAndView(&tabItemView1, &tabView1);
			this->addTabAndView(&tabItemView2, &tabView2);
			this->addTabAndView(&tabItemView3, &tabView3);
			this->addTabAndView(&tabItemView4, &tabView4);
			this->addTabAndView(&tabItemView5, &tabView5);
			this->setSelectedIndex(0);
		}
};