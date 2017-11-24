#ifndef GAMEOBJECTSPIKE_H
#define GAMEOBJECTSPIKE_H

#include "gameobject.h"

class GameObjectSpike : public GameObject
{
GAME_OBJECT_META(Type_Spike)
protected:
	void use();

private:
	GameObjectSpike(GameAbstractScene *pScene);
	~GameObjectSpike();

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTSPIKE_H
