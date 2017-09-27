#include "core.h"
#include "graphicscontroller.h"
#include "physicscontroller.h"
#include "gamecontroller.h"
#include "gameobject.h"

#include "gamescenemainmenu.h"
#include "gamesceneauthorsmenu.h"
#include "gamescenelevel.h"

bool GameController::process(AbstractControllerMessage* pMessage)
{
	switch (pMessage->type()) {
	case CMT_ControllerInit: {
		auto pMsg = msg_cast<ControllerInitMessage>(pMessage);
		if (pMsg)
			init();
		return true;
	}
	case CMT_ControllerUpdate: {
		auto pMsg = msg_cast<ControllerUpdateMessage>(pMessage);
		if (pMsg)
			update(pMsg->time, pMsg->dt);
		return true;
	}
	case CMT_GameMouseClick: {
		auto pMsg = msg_cast<GameMouseClickMessage>(pMessage);
		if (pMsg)
			mouseClick(pMsg->x, pMsg->y);
		return true;
	}
	case CMT_GameOver: {
		return true;
	}
	case CMT_GameObjectUse: {
		auto pMsg = msg_cast<GameObjectUseMessage>(pMessage);
		if (pMsg)
			pMsg->pGameObject->use();
		return true;
	}
	case CMT_GameChangeScene: {
		auto pMsg = msg_cast<GameChangeSceneMessage>(pMessage);
		if (pMsg)
			changeLevel(pMsg->sceneId);
		return true;
	}
	default: break;
	}
	return false;
}

GameController::GameController() :
	m_scenes(),
	m_currentSceneId(GameSceneId_None)
{
}

GameController::~GameController()
{
}

void GameController::init()
{
	m_scenes[GameSceneId_MainMenu] = new GameSceneMainMenu();
	m_scenes[GameSceneId_Authors] = new GameSceneAuthorsMenu();
	m_scenes[GameSceneId_SelectLevel] = nullptr;
	m_scenes[GameSceneId_Level] = new GameSceneLevel();
	changeLevel(GameSceneId_MainMenu);
}

void GameController::update(uint64_t time, uint32_t dt)
{
	m_scenes[m_currentSceneId]->updateScene(time, dt);
}

void GameController::mouseClick(int32_t x, int32_t y)
{
	m_scenes[m_currentSceneId]->mouseClick(x, y);
}

void GameController::changeLevel(GameSceneId id)
{
	if (m_currentSceneId == id)
		return;

	m_currentSceneId = id;
	Core::getController<GraphicsController>()->setCurrentScene(m_scenes[id]->graphicsScene());
	Core::getController<PhysicsController>()->setCurrentScene(m_scenes[id]->physicsScene());
}
