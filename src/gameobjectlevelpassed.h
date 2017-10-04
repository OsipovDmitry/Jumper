#ifndef GAMEOBJECTLEVELPASSED_H
#define GAMEOBJECTLEVELPASSED_H

#include "gameobject.h"

class GameObjectLevelPassed : public GameObject
{
public:
protected:
	void use();

private:
	GameObjectLevelPassed(GameAbstractScene *pScene);

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTLEVELPASSED_H
