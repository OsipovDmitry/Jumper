#ifndef GAMEOBJECTMODIFIEROFFSET_H
#define GAMEOBJECTMODIFIEROFFSET_H

#include "glm/vec2.hpp"
#include "gameobjectabstractmodifier.h"

class GameObjectModifierOffset : public GameObjectAbstractModifier
{

protected:
	GameObjectModifierOffset(GameObject *pObject, const glm::vec2& offset, const float velocity);
	~GameObjectModifierOffset();

	void update(uint32_t dt);

private:
	glm::vec2 m_offsetNorm;
	float m_offsetAbs, m_offsetVel, m_offsetCur;
	int m_sign;

	friend class GameObject;
};

#endif // GAMEOBJECTMODIFIEROFFSET_H
