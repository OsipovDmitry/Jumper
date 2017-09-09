#ifndef GAMEOBJECTPLAYER_H
#define GAMEOBJECTPLAYER_H

#include "gameobject.h"

class GameObjectPlayer : public GameObject
{
public:
protected:
private:
	GameObjectPlayer(GameAbstractScene *pScene);
	~GameObjectPlayer();

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTPLAYER_H
