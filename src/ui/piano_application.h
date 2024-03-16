#pragma once

#include "grafica/application.h"
#include "devices/piano/piano.h"

namespace ui {
	class PianoApplication : public grafica::Application {
		public:
			static PianoApplication& getInstance();

			void begin() override;
			void onTick() override;
			void onRender() override;

			devices::Piano &getPiano();

		private:
			PianoApplication();

			devices::Piano _piano = devices::Piano(180, 18);
	};
}