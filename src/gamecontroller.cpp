#include "core.h"
#include "graphicscontroller.h"
#include "physicscontroller.h"
#include "gamescenelevel.h"
#include "gamecontroller.h"

bool GameController::process(AbstractControllerMessage* pMessage)
{
	switch (pMessage->type()) {
	case CMT_ControllerUpdate: {
		auto *pMsg = msg_cast<ControllerUpdateMessage>(pMessage);
		if (pMsg)
			update(pMsg->time, pMsg->dt);
		break;
	}
	case CMT_GameMouseClick: {
		auto *pMsg = msg_cast<GameMouseClickMessage>(pMessage);
		if (pMsg)
			mouseClick(pMsg->x, pMsg->y);
		break;
	}
	case CMT_GameOver: {
		break;
	}
	default: break;
	}
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
		pLevel = new GameSceneLevel();
		Core::getController<GraphicsController>()->setCurrentScene(pLevel->graphicsScene());
		Core::getController<PhysicsController>()->setCurrentScene(pLevel->physicsScene());
	}
	pLevel->update(time, dt);
}

void GameController::mouseClick(int32_t x, int32_t y)
{
	pLevel->mouseClick(x, y);
}
