#include "core.h"
#include "graphicscontroller.h"
#include "physicscontroller.h"
#include "gamecontroller.h"
#include "gameobject.h"

#include "gamescenemainmenu.h"
#include "gamescenelevel.h"

bool GameController::process(AbstractControllerMessage* pMessage)
{
	switch (pMessage->type()) {
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
		auto pMsg = msg_cast<GameObjectUse>(pMessage);
		if (pMsg)
			pMsg->pGameObject->use();
		return true;
	}
	default: break;
	}
	return false;
}

GameController::GameController() :
	pLevel(nullptr)
{
}

GameController::~GameController()
{
	delete pLevel;
}

void GameController::update(uint64_t time, uint32_t dt)
{
	if (!pLevel) {
		pLevel = new GameSceneMainMenu();
		Core::getController<GraphicsController>()->setCurrentScene(pLevel->graphicsScene());
		Core::getController<PhysicsController>()->setCurrentScene(pLevel->physicsScene());
	}
	pLevel->updateScene(time, dt);
}

void GameController::mouseClick(int32_t x, int32_t y)
{
	pLevel->mouseClick(x, y);
}
