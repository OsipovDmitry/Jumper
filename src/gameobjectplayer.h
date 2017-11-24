#ifndef GAMEOBJECTPLAYER_H
#define GAMEOBJECTPLAYER_H

#include "gameobject.h"

class GameObjectPlayer : public GameObject
{
GAME_OBJECT_META(Type_Player)
public:
	void resetVelocity();

protected:
	void update(uint32_t dt);
	void use();

private:
	GameObjectPlayer(GameAbstractScene *pScene);
	~GameObjectPlayer();

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTPLAYER_H
