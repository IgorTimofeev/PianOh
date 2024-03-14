#include "workspace.h"
#include "grafica/display.h"
#include "element.h"
#include "grafica/animations/animation.h"

namespace grafica {
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
		setWorkspace(this);
	}

	void Workspace::invalidateLayout() {
		_isMeasured = false;
		_isArranged = false;
	}

	void Workspace::invalidateRender() {
		_isRendered = false;
	}

	void Workspace::invalidate() {
		invalidateLayout();
		invalidateRender();
	}

	void Workspace::addAnimation(Element *element, Animation* animation) {
		_animations.emplace_back(element, animation);
	}

	void Workspace::animate() {
		if (_animations.empty())
			return;

		auto time = millis();

		for (int i = 0; i < _animations.size(); i++) {
			auto elementAndAnimation = _animations[i];

			if (elementAndAnimation.second->tick(elementAndAnimation.first, time)) {
				_animations.erase(_animations.begin() + i);
				i--;
			}
		}
	}

	void Workspace::tick() {
		animate();

		Layout::tick();
	}
}