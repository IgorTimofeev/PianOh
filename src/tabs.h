#pragma once

#include "Arduino.h"
#include "ui/elements/layout.h"
#include "ui/elements/tab_bar.h"
#include "ui/elements/image.h"

#include "resources/images/gradient.h"
#include "resources/images/flame.h"
#include "resources/images/wave.h"

using namespace ui;

class TabItemView : public SelectorItem {
	public:
		TabItemView(uint16_t* pixelsOn, uint16_t* pixelsOff) : _pixelsOn(pixelsOn), _pixelsOff(pixelsOff) {
			// Background rect
			addChild(&_rectangle);

			// Image
			_image.setSize(Size(40, 40));
			_image.setMargin(Margin(10));
			_image.setPixels(pixelsOff);
			addChild(&_image);
		}

		void setSelected(const bool &value) override {
			_rectangle.setFillColor(value ? Color::black : Color::white);
			_image.setPixels(value ? _pixelsOn : _pixelsOff);
		}

	private:
		Rectangle _rectangle = Rectangle(Color::black);
		Image _image = Image();

		uint16_t* _pixelsOn;
		uint16_t* _pixelsOff;
};

class TabView1 : public StackLayout {
	public:
		SevenSegment sevenSegment = SevenSegment();

		TabView1() {
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

class TabView2 : public StackLayout {
	public:
		Slider slider = Slider();
		Text text = Text();

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
};

class TabView3 : public Layout {
	public:
		TabView3() {
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
		TabItemView tabItemView1 = TabItemView(const_cast<uint16_t *>(GRADIENT_ON), const_cast<uint16_t *>(GRADIENT_OFF));
		TabView1 tabView1 = TabView1();

		TabItemView tabItemView2 = TabItemView(const_cast<uint16_t *>(WAVE_ON), const_cast<uint16_t *>(WAVE_OFF));
		TabView2 tabView2 = TabView2();

		TabItemView tabItemView3 = TabItemView(const_cast<uint16_t *>(FLAME_ON), const_cast<uint16_t *>(FLAME_OFF));
		TabView3 tabView3 = TabView3();

		PianoTabBar() {
			this->addTabAndView(&tabItemView1, &tabView1);
			this->addTabAndView(&tabItemView2, &tabView2);
			this->addTabAndView(&tabItemView3, &tabView3);

			this->setSelectedIndex(1);
		}
};