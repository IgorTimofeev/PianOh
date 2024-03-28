#include <cstdint>
#include "piano_application.h"
#include "tabs/tab_bar.h"
#include "resources/fonts.h"

using namespace grafica;

namespace ui {
	PianoApplication &PianoApplication::getInstance() {
		static PianoApplication instance;

		return instance;
	}

	PianoApplication::PianoApplication() : Application(
		Size(TFT_HEIGHT, TFT_WIDTH),
		25,
		21,
		22,
		4,
		0
	) {

	}

	void PianoApplication::begin() {
		Application::begin();

		// Screen
		getScreen().setDefaultFont(resources::fonts::unscii16);

		// Workspace
		getWorkspace().addChild(new TabBar());
		//getWorkspace().addChild(new Rectangle(Color::water));

		// Piano
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