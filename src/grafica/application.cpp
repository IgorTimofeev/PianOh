#include "application.h"

namespace grafica {
	void Application::begin() {
		_display.begin();
	}

	void Application::tick() {
		// Tick
		if (micros() > _tickDeadline) {
			onTick();

			_tickDeadline = micros() + 1000000 / _tps;
		}

		// Render
		if (micros() > _renderDeadline) {
			onRender();

			_renderDeadline = micros() + 1000000 / _fps;
		}
	}

	void Application::onTick() {
		_display.tick();
	}

	void Application::onRender() {
		_display.render();
	}
}