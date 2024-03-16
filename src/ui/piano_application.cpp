#include <cstdint>
#include "piano_application.h"
#include "tabs/tab_bar.h"

using namespace grafica;

namespace ui {
	PianoApplication &PianoApplication::getInstance() {
		static PianoApplication instance;

		return instance;
	}

	PianoApplication::PianoApplication() : Application(Size(TFT_WIDTH, TFT_HEIGHT), 4, 5, 9, 8, 13) {

	}

	void PianoApplication::begin() {
		Application::begin();

		getWorkspace().addChild(new TabBar());

		_piano.begin();
	}

	void PianoApplication::onTick() {
		Application::onTick();

		_piano.tick();
	}

	void PianoApplication::onRender() {
		Application::onRender();

		_piano.renderStrip();
	}

	devices::Piano &PianoApplication::getPiano() {
		return _piano;
	}
}