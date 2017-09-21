#include "glm/geometric.hpp"

#include "gameobject.h"
#include "gameobjectmodifieroffset.h"
#include "types.h"

GameObjectModifierOffset::GameObjectModifierOffset(GameObject *pObject, const glm::vec2& offset, const float velocity) :
	GameObjectAbstractModifier(pObject),
	m_offsetVel(velocity),
	m_offsetCur(0.0f),
	m_sign(1)
{
	m_offsetAbs = glm::length(offset);
	assert(m_offsetAbs > 0.0001f);
	m_offsetNorm = offset / m_offsetAbs;
}

GameObjectModifierOffset::~GameObjectModifierOffset()
{
}

void GameObjectModifierOffset::update(uint32_t dt)
{
	float delta = m_sign * m_offsetVel * dt * 0.001f;
	m_offsetCur += delta;
	if (m_offsetCur > m_offsetAbs) {
		m_offsetCur = 2 * m_offsetAbs - m_offsetCur;
		m_sign *= -1;
	}
	if (m_offsetCur < 0.0f) {
		m_offsetCur = 0.0f - m_offsetCur;
		m_sign *= -1;
	}
	Transform transform = m_pGameObject->transform();
	transform.pos += m_offsetNorm * delta;
	m_pGameObject->setTransform(transform);
}
