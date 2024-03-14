#pragma once

#include "Arduino.h"
#include "grafica/elements/layout.h"
#include "grafica/elements/seven_segment.h"

using namespace grafica;

namespace ui {
	class FlameTab : public Layout {
		public:
			SevenSegment sevenSegment = SevenSegment();

			FlameTab() {
				setAlignment(Alignment::center);

				// SevenSegment
				sevenSegment.setSegmentThickness(3);
				sevenSegment.setSegmentLength(9);
				sevenSegment.setSpacing(3);
				sevenSegment.setDigitCount(6);
				sevenSegment.setHorizontalAlignment(Alignment::center);

				sevenSegment.addEventHandler([this](Event &event) {
					if (event.getType() == EventType::touchDown) {
						sevenSegment.setValue(sevenSegment.getValue() + 1);
					}
				});

				addChild(&sevenSegment);
			}
	};
}