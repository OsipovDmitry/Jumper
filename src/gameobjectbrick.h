#ifndef GAMEOBJECTBRICK_H
#define GAMEOBJECTBRICK_H

#include "gameobject.h"

class GameObjectBrick : public GameObject
{
GAME_OBJECT_META(Type_Brick)
public:
protected:
	void use();

private:
	GameObjectBrick(GameAbstractScene *pScene);
	~GameObjectBrick();

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTBRICK_H
