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

		private:
			String _text = "Hello";
	};
}
