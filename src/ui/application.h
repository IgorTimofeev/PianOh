#pragma once

#include "grafica/elements/workspace.h"
#include "grafica/color.h"
#include "grafica/number.h"
#include "grafica/display.h"

#include "devices/piano/piano.h"
#include "devices/piano/effects/effect.h"
#include "devices/piano/effects/flame_effect.h"
#include "devices/piano/effects/rainbow_effect.h"
#include "devices/piano/effects/water_effect.h"
#include "devices/piano/effects/test_effect.h"
#include "devices/piano/effects/gradient_effect.h"
#include "devices/piano/effects/strobe_effect.h"

#include "tabs/tab_bar.h"

using namespace grafica;

namespace ui {
	class Application {
		public:
			static Application& getInstance() {
				static Application instance;

				return instance;
			}

			Display display = Display(4, 5, 9, 8);
			devices::Piano piano = devices::Piano(180, 18);

			void begin() {
				display.begin();
				piano.begin();
				display.getWorkspace().addChild(new TabBar());
			}

			void loop() {
				// Tick
				if (micros() > _tickDeadline) {
					display.tick();
					piano.tick();

					_tickDeadline = micros() + 1000000 / _tps;
				}

				// Render
				if (micros() > _renderDeadline) {
					display.render();
					piano.renderStrip(micros());

					_renderDeadline = micros() + 1000000 / _fps;
				}
			}

		private:
			Application() = default;

		private:
			uint32_t _tickDeadline = 0;
			uint32_t _renderDeadline = 0;
			uint16_t _tps = 20;
			uint16_t _fps = 30;
	};
}