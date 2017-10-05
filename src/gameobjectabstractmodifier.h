#ifndef GAMEOBJECTABSTRACTMODIFIER_H
#define GAMEOBJECTABSTRACTMODIFIER_H

#include <inttypes.h>
#include <string>

class GameObject;

class GameObjectAbstractModifier
{
public:
	virtual bool setParam(const std::string& key, const std::string& value);

protected:
	GameObjectAbstractModifier(GameObject *pObject);
	virtual ~GameObjectAbstractModifier() = default;

	virtual void update(uint32_t) {}

	GameObject *m_pGameObject;

	friend class GameObject;
};

#endif // GAMEOBJECTABSTRACTMODIFIER_H
