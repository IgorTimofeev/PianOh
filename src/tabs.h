#pragma once

#include "Arduino.h"
#include "ui/elements/layout.h"
#include "ui/elements/tab_bar.h"

using namespace ui;

class TabItem {
	public:
		explicit TabItem(const String& name) {
			this->name = name;
		}

		String name;
};

class TabItemView : public Layout {
	public:
		TabItemView() {
			rectangle.setCornerRadius(5);
			addChild(&rectangle);

			text.setAlignment(Alignment::center);
			text.setMargin(Margin(10));
			addChild(&text);
		}

		Rectangle rectangle = Rectangle(Color::black);
		Text text = Text();
};

class Tab1 : public StackLayout {
	public:
		SevenSegment sevenSegment = SevenSegment();

		Tab1() {
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

class Tab2 : public StackLayout {
	public:
		Slider slider = Slider();
		Text text = Text();

		Tab2() {
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

class Tab3 : public Layout {
	public:
		Tab3() {
			setAlignment(Alignment::center);

			addChild(&rectangle);

			text.setText("Timer");
			text.setAlignment(Alignment::center, Alignment::center);
			text.setMargin(Margin(10));
			addChild(&text);
		}

		Rectangle rectangle = Rectangle(Color::black);
		Text text = Text();
};

class PianoTabBar : public TabBar<TabItem, TabItemView> {
	public:
		Tab1 tab1 = Tab1();
		Tab2 tab2 = Tab2();
		Tab3 tab3 = Tab3();

		PianoTabBar() {
			this->addTabAndView(TabItem("1"), &tab1);
			this->addTabAndView(TabItem("2"), &tab2);
			this->addTabAndView(TabItem("Penis"), &tab3);

			this->setSelectedIndex(1);
		}

	protected:
		TabItemView* createItemView() override {
			return new TabItemView();
		}

		void itemToView(const TabItem& item, TabItemView* view) override {
			view->text.setText(item.name);
		}

		void setItemViewSelected(TabItemView* view, const bool &value) override {
			view->rectangle.setFillColor(value ? Color::white : Color::black);
			view->text.setColor(value ? Color::black : Color::white);
		}
};