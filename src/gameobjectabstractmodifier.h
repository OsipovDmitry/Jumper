#ifndef GAMEOBJECTABSTRACTMODIFIER_H
#define GAMEOBJECTABSTRACTMODIFIER_H

#include <inttypes.h>

class GameObject;

class GameObjectAbstractModifier
{
protected:
	GameObjectAbstractModifier(GameObject *pObject);
	virtual ~GameObjectAbstractModifier() = default;

	virtual void update(uint32_t) {}

	GameObject *m_pGameObject;

	friend class GameObject;
};

#endif // GAMEOBJECTABSTRACTMODIFIER_H
