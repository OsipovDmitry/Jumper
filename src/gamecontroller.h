#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "abstractcontroller.h"

class PhysicsGeometry;
class GameSceneLevel;

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

	GameSceneLevel *pLevel;

	friend class Core;
};

class GameMouseClickMessage : public AbstractControllerMessage {
public:
	GameMouseClickMessage(int32_t xVal, int32_t yVal) : AbstractControllerMessage(CMT_GameMouseClick), x(xVal), y(yVal) {}
	static ControllerMessageType typeOfClass() { return CMT_GameMouseClick; }

	int32_t x, y;
};

class GameObjectsCollisionMessage : public AbstractControllerMessage {
public:
	GameObjectsCollisionMessage(PhysicsGeometry *p1, PhysicsGeometry *p2) : AbstractControllerMessage(CMT_GameObjectsCollision), pGeom1(p1), pGeom2(p2) {}
	static ControllerMessageType typeOfClass() { return CMT_GameObjectsCollision; }

	PhysicsGeometry *pGeom1, *pGeom2;
};

DECLARE_SIMPLE_MESSAGE(GameOverMessage, CMT_GameOver)


#endif // GAMECONTROLLER_H
