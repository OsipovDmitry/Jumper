#ifndef GAMEOBJECTBROKENBRICK_H
#define GAMEOBJECTBROKENBRICK_H

#include "gameobject.h"

class GraphicsObject;
class PhysicsObject;
class PhysicsGeometry;

class GameObjectBrokenBrick : public GameObject
{
public:
	void breakDown();

protected:
	GameObjectBrokenBrick(GameAbstractScene *pScene);
	~GameObjectBrokenBrick();

private:
	bool m_isWhole;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTBROKENBRICK_H
