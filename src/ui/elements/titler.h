#pragma once

#include "grafica/elements/stack_layout.h"
#include "grafica/elements/element.h"
#include "grafica/elements/text.h"

using namespace grafica;

namespace ui {
	class Titler : public StackLayout {
		public:
			Titler() {
				setSpacing(5);

				addChild(&_titleText);
			}

			explicit Titler(const String& title) : Titler() {
				_titleText.setText(title);
			}

		private:
			Text _titleText = Text();
	};
}