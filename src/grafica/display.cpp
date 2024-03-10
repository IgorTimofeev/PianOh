#include "display.h"
#include "grafica/elements/workspace.h"

namespace grafica {
	Workspace &Display::getWorkspace() {
		return _workspace;
	}

	void Display::render() {
		_workspace.measure(*this);
		_workspace.arrange();
		_workspace.render(*this);
	}
}
