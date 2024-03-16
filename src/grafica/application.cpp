#include "application.h"
#include "point.h"
#include "event.h"

namespace grafica {
	Application::Application(const Size &size, const uint8_t &sdaPin, const uint8_t &sclPin, const uint8_t &rstPin, const uint8_t &intPin, const uint8_t &ledPin) :
		_screen(
			size,
			sdaPin,
			sclPin,
			rstPin,
			intPin,
			ledPin
		),
		_workspace()
	{
		_workspace.setSize(_screen.getResolution());

		// Touch
		_screen.addOnTouchDown([this](const Point& point) {
			Serial.print("Touch doan:");
			Serial.println();

			auto event = TouchDownEvent(point);
			_workspace.handleEvent(event);
		});

		_screen.addOnTouchDrag([this](const Point& point) {
			auto event = TouchDragEvent(point);
			_workspace.handleEvent(event);
		});

		_screen.addOnTouchUp([this](const Point& point) {
			auto event = TouchUpEvent(point);
			_workspace.handleEvent(event);
		});

		// Pinch
		_screen.addOnPinchDown([this](const Point& point1, const Point& point2) {
			auto event = PinchDownEvent(point1, point2);
			_workspace.handleEvent(event);
		});

		_screen.addOnPinchDrag([this](const Point& point1, const Point& point2) {
			auto event = PinchDragEvent(point1, point2);
			_workspace.handleEvent(event);
		});

		_screen.addOnPinchUp([this](const Point& point1, const Point& point2) {
			auto event = PinchUpEvent(point1, point2);
			_workspace.handleEvent(event);
		});
	}

	void Application::begin() {
		_screen.begin();
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
		_screen.tick();
		_workspace.tick();
	}

	void Application::onRender() {
		_workspace.measure(_screen);
		_workspace.arrange();
		_workspace.render(_screen);
	}
}