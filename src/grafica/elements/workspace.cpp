#include "workspace.h"
#include "grafica/display.h"

namespace grafica {
	void Workspace::invalidateLayout() {
		_isMeasured = false;
		_isArranged = false;
		_isRendered = false;
	}

	void Workspace::render(Display &display) {
		if (_isRendered)
			return;

		Layout::render(display);
		display.flush();
		_isRendered = true;
	}

	void Workspace::arrange() {
		if (_isArranged)
			return;

		Layout::arrange(Bounds(getSize()));
		_isArranged = true;
	}

	void Workspace::measure(Display &display) {
		if (_isMeasured)
			return;

		Layout::measure(display, getSize());
		_isMeasured = true;
	}

	Workspace::Workspace() {
		setFirstParent(this);
	}
}