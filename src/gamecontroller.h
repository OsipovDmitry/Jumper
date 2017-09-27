#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <array>

#include "abstractcontroller.h"

class PhysicsGeometry;
class GameAbstractScene;
class GameObject;

class GameController : public AbstractController
{
public:
	static ControllerType controllerType() { return ControllerType_Game; }

protected:
	virtual bool process(AbstractControllerMessage *pMessage);

private:
	GameController();
	~GameController();

	void init();
	void update(uint64_t time, uint32_t dt);
	void mouseClick(int32_t x, int32_t y);

	void changeLevel(GameSceneId id);

	std::array<GameAbstractScene*, GameSceneId_Count> m_scenes;
	GameSceneId m_currentSceneId;

	friend class Core;
};

class GameMouseClickMessage : public AbstractControllerMessage {
public:
	GameMouseClickMessage(int32_t xVal, int32_t yVal) : AbstractControllerMessage(CMT_GameMouseClick), x(xVal), y(yVal) {}
	static ControllerMessageType typeOfClass() { return CMT_GameMouseClick; }

	int32_t x, y;
};

DECLARE_SIMPLE_MESSAGE(GameOverMessage, CMT_GameOver)

class GameObjectUseMessage : public AbstractControllerMessage {
public:
	GameObjectUseMessage(GameObject *pObject) : AbstractControllerMessage(CMT_GameObjectUse), pGameObject(pObject) {}
	static ControllerMessageType typeOfClass() { return CMT_GameObjectUse; }

	GameObject *pGameObject;
};

class GameChangeSceneMessage : public AbstractControllerMessage {
public:
	GameChangeSceneMessage(GameSceneId id) : AbstractControllerMessage(CMT_GameChangeScene), sceneId(id) {}
	static ControllerMessageType typeOfClass() { return CMT_GameChangeScene; }

	GameSceneId sceneId;
};

#endif // GAMECONTROLLER_H
