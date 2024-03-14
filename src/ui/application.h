#pragma once

#include "grafica/display.h"
#include "devices/piano/piano.h"

using namespace grafica;

namespace ui {
	class Application {
		public:
			static Application& getInstance();

			Display display = Display(4, 5, 9, 8);
			devices::Piano piano = devices::Piano(180, 18);

			void begin();

			void loop();

		private:
			Application() = default;

		private:
			uint32_t _tickDeadline = 0;
			uint32_t _renderDeadline = 0;
			uint16_t _tps = 20;
			uint16_t _fps = 30;
	};
}