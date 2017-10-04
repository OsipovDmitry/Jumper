#ifndef GAMEOBJECTPLAYER_H
#define GAMEOBJECTPLAYER_H

#include "gameobject.h"

class PhysicsBody;

class GameObjectPlayer : public GameObject
{
public:
	PhysicsBody *physicsBody() const;

protected:
	void update(uint32_t dt);
	void use();

private:
	GameObjectPlayer(GameAbstractScene *pScene);
	~GameObjectPlayer();

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTPLAYER_H
