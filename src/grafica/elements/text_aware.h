#pragma once

#include "element.h"
#include "grafica/color.h"

namespace grafica {
	class TextAware : virtual public Element {
		public:
			const String &getText() const {
				return _text;
			}

			void setText(const String &value) {
				_text = value;
			}

			uint8_t getFontSize() const {
				return _fontSize;
			}

			void setFontSize(uint8_t value) {
				_fontSize = value;
			}

		private:
			String _text = "Hello";
			uint8_t _fontSize = 2;
	};
}
