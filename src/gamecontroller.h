#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

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

	void update(uint64_t time, uint32_t dt);
	void mouseClick(int32_t x, int32_t y);

	GameAbstractScene *pLevel;

	friend class Core;
};

class GameMouseClickMessage : public AbstractControllerMessage {
public:
	GameMouseClickMessage(int32_t xVal, int32_t yVal) : AbstractControllerMessage(CMT_GameMouseClick), x(xVal), y(yVal) {}
	static ControllerMessageType typeOfClass() { return CMT_GameMouseClick; }

	int32_t x, y;
};

DECLARE_SIMPLE_MESSAGE(GameOverMessage, CMT_GameOver)

class GameObjectUse : public AbstractControllerMessage {
public:
	GameObjectUse(GameObject *pObject) : AbstractControllerMessage(CMT_GameObjectUse), pGameObject(pObject) {}
	static ControllerMessageType typeOfClass() { return CMT_GameObjectUse; }

	GameObject *pGameObject;
};

#endif // GAMECONTROLLER_H
