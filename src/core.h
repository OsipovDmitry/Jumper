#ifndef CORE_H
#define CORE_H

#include <inttypes.h>
#include <array>

#include "abstractcontroller.h"

class GraphicsController;
class PhysicsController;
class GameController;
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
	void update(uint64_t time, uint32_t dt);
	void mouseClick(int32_t x, int32_t y);
};

DECLARE_SIMPLE_MESSAGE(CoreExitMessage, CMT_CoreExit)
DECLARE_SIMPLE_MESSAGE(CoreInitMessage, CMT_CoreInit)

class CoreUpdateMessage : public AbstractControllerMessage {
public:
	CoreUpdateMessage(uint64_t timeVal, uint32_t dtVal) : AbstractControllerMessage(CMT_CoreUpdate), time(timeVal), dt(dtVal) {}
	static ControllerMessageType typeOfClass() { return CMT_CoreUpdate; }

	uint64_t time;
	uint32_t dt;
};

class CoreMouseClickMessage : public AbstractControllerMessage {
public:
	CoreMouseClickMessage(int32_t xVal, int32_t yVal) : AbstractControllerMessage(CMT_CoreMouseClick), x(xVal), y(yVal) {}
	static ControllerMessageType typeOfClass() { return CMT_CoreMouseClick; }

	int32_t x, y;
};

#endif // CORE_H
