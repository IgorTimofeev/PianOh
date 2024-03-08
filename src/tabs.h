#pragma once

#include "Arduino.h"
#include "ui/elements/layout.h"
#include "ui/elements/tab_bar.h"

using namespace ui;

class PianoTab {
	public:
		explicit PianoTab(const String& name) : _name(name) {

		}

	private:
		String _name;
};

class Tab1 : public StackLayout {
	public:
		SevenSegment sevenSegment = SevenSegment();

		Tab1() {
			setHorizontalAlignment(Alignment::center);
			setVerticalAlignment(Alignment::center);

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
			setHorizontalAlignment(Alignment::center);
			setVerticalAlignment(Alignment::center);

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

class PianoTabBar : public TabBar<PianoTab> {
	public:
		Tab1 tab1 = Tab1();
		Tab2 tab2 = Tab2();

		PianoTabBar() {
			addTabAndView(PianoTab("Tab 1"), &tab1);
			addTabAndView(PianoTab("Tab 2"), &tab2);
		}
};