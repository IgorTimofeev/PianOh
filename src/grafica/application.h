#pragma once

#include "display.h"

namespace grafica {
	class Application {
		public:
			Application(int8_t sdaPin, int8_t sclPin, uint8_t rstPin, uint8_t intPin, uint8_t ledPin) :
				_display(
					sdaPin,
					sclPin,
					rstPin,
					intPin,
					ledPin
				)
			{

			}

			virtual void begin();
			virtual void tick();

			virtual void onTick();
			virtual void onRender();

			Display& getDisplay() {
				return _display;
			}

			const uint16_t &getTps() const {
				return _tps;
			}

			void setTps(const uint16_t &tps) {
				_tps = tps;
			}

			const uint16_t &getFps() const {
				return _fps;
			}

			void setFps(const uint16_t &fps) {
				_fps = fps;
			}

		private:
			Display _display;
			uint32_t _tickDeadline = 0;
			uint32_t _renderDeadline = 0;
			uint16_t _tps = 60;
			uint16_t _fps = 60;

	};
}