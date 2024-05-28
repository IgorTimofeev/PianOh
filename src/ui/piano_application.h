#pragma once

#include "grafica/application.h"
#include "devices/piano/piano.h"

using namespace grafica;

namespace ui {
	class PianoApplication : public Application {
		public:
			static PianoApplication& getInstance();

			void onTick() override;
			void onRender() override;

			void begin() override;

			devices::Piano &getPiano();

		private:
			PianoApplication();

			devices::Piano _piano = devices::Piano(177, 27);
	};
}