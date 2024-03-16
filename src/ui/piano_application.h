#pragma once

#include "grafica/application.h"
#include "devices/piano/piano.h"

namespace ui {
	class PianoApplication : public grafica::Application {
		public:
			static PianoApplication& getInstance();

			PianoApplication();

			void begin() override;
			void onTick() override;
			void onRender() override;

			devices::Piano &getPiano();

		private:
			devices::Piano _piano = devices::Piano(180, 18);
	};
}