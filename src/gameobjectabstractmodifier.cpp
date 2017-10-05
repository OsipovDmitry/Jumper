#include "gameobjectabstractmodifier.h"

bool GameObjectAbstractModifier::setParam(const std::string& key, const std::string& value)
{
	(void)value;

	static const std::string s_type = "type";

	if (key == s_type)
		return true;

	return false;
}

GameObjectAbstractModifier::GameObjectAbstractModifier(GameObject* pObject) :
	m_pGameObject(pObject)
{
}
