#include "display.h"
#include "elements/workspace.h"

namespace ui {
	Workspace &Display::getWorkspace() {
		return _workspace;
	}

	void Display::render() {
		_workspace.measure(*this);
		_workspace.arrange();
		_workspace.render(*this);
	}
}
