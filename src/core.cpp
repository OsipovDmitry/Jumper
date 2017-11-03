#include "core.h"
#include "renderwidget.h"
#include "renderer.h"
#include "graphicscontroller.h"
#include "physicscontroller.h"
#include "audiocontroller.h"
#include "gamecontroller.h"

Core *Core::s_pCore = nullptr;

Core *Core::instance()
{
	if (!s_pCore)
		s_pCore = new Core;
	return s_pCore;
}

void Core::deinit()
{
	delete s_pCore;
	s_pCore = nullptr;
}

void Core::run()
{
	instance()->m_pRenderWidget->show();
}

RenderWidget *Core::renderWidget() const
{
	return m_pRenderWidget;
}

bool Core::process(AbstractControllerMessage* pMessage)
{
	switch (pMessage->type()) {
	case CMT_CoreExit: {
		exit();
		return true;
	}
	case CMT_CoreInit: {
		init();
		return true;
	}
	case CMT_CoreUpdate: {
		auto pMsg = msg_cast<CoreUpdateMessage>(pMessage);
		if (pMsg)
			update(pMsg->dt);
		return true;
	}
	case CMT_CoreMouseClick: {
		auto pMsg = msg_cast<CoreMouseClickMessage>(pMessage);
		if (pMsg)
			mouseClick(pMsg->x, pMsg->y);
		return true;
	}
	case CMT_CoreKeyPress: {
		auto pMsg = msg_cast<CoreKeyPressMessage>(pMessage);
		if (pMsg)
			keyPress(pMsg->keyCode);
		return true;
	}
	case CMT_CoreKeyRelease: {
		auto pMsg = msg_cast<CoreKeyReleaseMessage>(pMessage);
		if (pMsg)
			keyRelease(pMsg->keyCode);
		return true;
	}
	case CMT_CoreTilt: {
		auto pMsg = msg_cast<CoreTiltMessage>(pMessage);
		if (pMsg)
			tilt(pMsg->x, pMsg->y);
		return true;
	}
	default: break;
	}
	return false;
}

Core::Core() :
	AbstractController(),
	m_pRenderWidget(new RenderWidget())
{
	m_controllers[ControllerType_Core] = this;
	m_controllers[ControllerType_Graphics] = new GraphicsController();
	m_controllers[ControllerType_Physics] = new PhysicsController();
	m_controllers[ControllerType_Audio] = new AudioController();
	m_controllers[ControllerType_Game] = new GameController();
}

Core::~Core()
{
	delete m_controllers[ControllerType_Game];
	delete m_controllers[ControllerType_Audio];
	delete m_controllers[ControllerType_Physics];
	delete m_controllers[ControllerType_Graphics];

	delete m_pRenderWidget;
}

void Core::exit()
{
	m_pRenderWidget->close();
}

void Core::init()
{
	for (auto it = m_controllers.begin(); it != m_controllers.end(); ++it) {
		if (*it == static_cast<AbstractController*>(this)) // Пропускаем компонент Core
			continue;
		(*it)->sendMessage(new ControllerInitMessage());
	}
}

void Core::update(uint32_t dt)
{
	for (auto it = m_controllers.begin(); it != m_controllers.end(); ++it) {
		if (*it == static_cast<AbstractController*>(this)) // Пропускаем компонент Core
			continue;
		(*it)->sendMessage(new ControllerUpdateMessage(dt));
		(*it)->readMessages();
	}
}

void Core::mouseClick(int32_t x, int32_t y)
{
	m_controllers[ControllerType_Game]->sendMessage(new GameMouseClickMessage(x, y));
}

void Core::keyPress(KeyCode keyCode)
{
	m_controllers[ControllerType_Game]->sendMessage(new GameKeyPressMessage(keyCode));
}

void Core::keyRelease(KeyCode keyCode)
{
	m_controllers[ControllerType_Game]->sendMessage(new GameKeyReleaseMessage(keyCode));
}

void Core::tilt(float x, float y)
{
	m_controllers[ControllerType_Game]->sendMessage(new GameTiltMessage(x, y));
}
