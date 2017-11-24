#ifndef GAMEOBJECTLEVELPASSED_H
#define GAMEOBJECTLEVELPASSED_H

#include "gameobject.h"
#include "types.h"

class GameObjectLevelPassed : public GameObject
{
GAME_OBJECT_META(Type_LevelPassed)
public:
protected:
	void use();

private:
	GameObjectLevelPassed(GameAbstractScene *pScene, GameLevelId id);

	GameLevelId m_levelId;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTLEVELPASSED_H
