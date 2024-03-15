#include "application.h"
#include "tabs/tab_bar.h"

using namespace grafica;

namespace ui {
	Application &Application::getInstance() {
		static Application instance;

		return instance;
	}

	void Application::loop() {
		// Tick
		if (micros() > _tickDeadline) {
			display.tick();
			piano.tick();

			_tickDeadline = micros() + 1000000 / _tps;
		}

		// Render
		if (micros() > _renderDeadline) {
			display.render();
//			piano.renderStrip(micros());

			_renderDeadline = micros() + 1000000 / _fps;
		}
	}

	void Application::begin() {
		display.begin();
		piano.begin();
		display.getWorkspace().addChild(new TabBar());
	}
}