#ifndef GAMEOBJECTBRICK_H
#define GAMEOBJECTBRICK_H

#include "gameobject.h"

class GameObjectBrick : public GameObject
{
public:
protected:
	void use();

private:
	GameObjectBrick(GameAbstractScene *pScene);
	~GameObjectBrick();

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTBRICK_H
