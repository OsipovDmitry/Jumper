#ifndef CORE_H
#define CORE_H

#include <inttypes.h>
#include <array>

#include "abstractcontroller.h"

//class GraphicsController;
//class PhysicsController;
//class GameController;
class RenderWidget;

class Core : public AbstractController
{
public:
	static ControllerType controllerType() { return ControllerType_Core; }

	static void deinit();
	static void run();

	template<typename ControllerClass = Core>
	static ControllerClass *getController() {
		return static_cast<ControllerClass*>(Core::instance()->m_controllers[ControllerClass::controllerType()]);
	}

	RenderWidget *renderWidget() const;

protected:
	bool process(AbstractControllerMessage *pMessage);

private:
	static Core *s_pCore;
	static Core *instance();

	std::array<AbstractController*, ControllerType_Count> m_controllers;
	RenderWidget *m_pRenderWidget;

	Core();
	~Core();

	void exit();
	void init();
	void update(uint32_t dt);
	void mouseClick(int32_t x, int32_t y);
	void keyPress(KeyCode keyCode);
	void keyRelease(KeyCode keyCode);
	void tilt(float x, float y);
};

DECLARE_SIMPLE_MESSAGE(CoreExitMessage, CMT_CoreExit)
DECLARE_SIMPLE_MESSAGE(CoreInitMessage, CMT_CoreInit)

class CoreUpdateMessage : public AbstractControllerMessage {
public:
	CoreUpdateMessage(uint32_t dtVal) : AbstractControllerMessage(CMT_CoreUpdate), dt(dtVal) {}
	static ControllerMessageType typeOfClass() { return CMT_CoreUpdate; }

	uint32_t dt;
};

class CoreMouseClickMessage : public AbstractControllerMessage {
public:
	CoreMouseClickMessage(int32_t xVal, int32_t yVal) : AbstractControllerMessage(CMT_CoreMouseClick), x(xVal), y(yVal) {}
	static ControllerMessageType typeOfClass() { return CMT_CoreMouseClick; }

	int32_t x, y;
};

class CoreKeyPressMessage : public AbstractControllerMessage {
public:
	CoreKeyPressMessage(KeyCode code) : AbstractControllerMessage(CMT_CoreKeyPress), keyCode(code) {}
	static ControllerMessageType typeOfClass() { return CMT_CoreKeyPress; }

	KeyCode keyCode;
};

class CoreKeyReleaseMessage : public AbstractControllerMessage {
public:
	CoreKeyReleaseMessage(KeyCode code) : AbstractControllerMessage(CMT_CoreKeyRelease), keyCode(code) {}
	static ControllerMessageType typeOfClass() { return CMT_CoreKeyRelease; }

	KeyCode keyCode;
};

class CoreTiltMessage : public AbstractControllerMessage {
public:
	CoreTiltMessage(float xVal, float yVal) : AbstractControllerMessage(CMT_CoreTilt), x(xVal), y(yVal) {}
	static ControllerMessageType typeOfClass() { return CMT_CoreTilt; }

	float x, y;
};

#endif // CORE_H
