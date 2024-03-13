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
using namespace devices::piano;

namespace ui {
	class Application {
		public:
			static Application& getInstance() {
				static Application instance;

				return instance;
			}

			// ---------------------------------- Display ----------------------------------

			Display display = Display(4, 5, 9, 8);
			uint32_t displayRenderDeadline = 0;

			void displayRender() {
				if (micros() <= displayRenderDeadline)
					return;

				display.readTouch();
				display.render();

				displayRenderDeadline = micros() + 1000000 / 30;
			}

			// ---------------------------------- UI ----------------------------------

//			TabBar tabBar;

			// ---------------------------------- Piano ----------------------------------

			devices::piano::Piano piano = devices::piano::Piano(180, 18);

			uint32_t pianoRenderDeadline = 0;

			void renderPianoStrip() {
				uint32_t time = millis();

				if (time <= pianoRenderDeadline)
					return;

				// Updating piano
				piano.renderStrip(time);

				pianoRenderDeadline = time + 1000 / 60;
			}

			void begin() {
				// Display
				display.begin();
//				display.getWorkspace().addChild(&tabBar);
				display.getWorkspace().addChild(new TabBar());

				// Piano
				piano.begin();
				piano.clearStrip();
			}

			void update() {
				displayRender();

				piano.readMidiEvents();
				renderPianoStrip();
			}

		private:
			Application() = default;
	};
}