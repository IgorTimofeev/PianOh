#pragma once

#include "Arduino.h"
#include "ui/elements/layout.h"
#include "ui/elements/tab_bar.h"

using namespace ui;

class TabItemView : public SelectorItem {
	public:
		explicit TabItemView(const String& name) {
			rectangle.setCornerRadius(5);
			addChild(&rectangle);

			text.setAlignment(Alignment::center);
			text.setMargin(Margin(10));
			text.setText(name);
			addChild(&text);
		}

		Rectangle rectangle = Rectangle(Color::black);
		Text text = Text();

		void setSelected(const bool &value) override {
			rectangle.setFillColor(value ? Color::white : Color::black);
			text.setColor(value ? Color::black : Color::white);
		}
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
		TabItemView tabItemView1 = TabItemView("7 segments");
		TabView1 tabView1 = TabView1();

		TabItemView tabItemView2 = TabItemView("Slider");
		TabView2 tabView2 = TabView2();

		TabItemView tabItemView3 = TabItemView("Test");
		TabView3 tabView3 = TabView3();

		PianoTabBar() {
			this->addTabAndView(&tabItemView1, &tabView1);
			this->addTabAndView(&tabItemView2, &tabView2);
			this->addTabAndView(&tabItemView3, &tabView3);

			this->setSelectedIndex(1);
		}
};