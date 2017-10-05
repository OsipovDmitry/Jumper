#include "glm/geometric.hpp"

#include "gameobject.h"
#include "gameobjectmodifieroffset.h"
#include "types.h"
#include "mathutils.h"

GameObjectModifierOffset::GameObjectModifierOffset(GameObject *pObject) :
	GameObjectAbstractModifier(pObject),
	m_offsetNorm(),
	m_offsetVel(0.0f),
	m_offsetCur(0.0f),
	m_sign(1)
{
}

bool GameObjectModifierOffset::setParam(const std::string& key, const std::string& value)
{
	if (GameObjectAbstractModifier::setParam(key, value))
		return true;

	static const std::string s_offsXTag = "x";
	static const std::string s_offsYTag = "y";
	static const std::string s_velocityTag = "velocity";

	if (key == s_offsXTag) {
		auto offs = offset();
        offs.x = static_cast<float>(stof(value.c_str()));
		setOffset(offs);
		return true;
	} else if (key == s_offsYTag) {
		auto offs = offset();
        offs.y = static_cast<float>(stof(value.c_str()));
		setOffset(offs);
		return true;
	} else if (key == s_velocityTag) {
        setVelocity(static_cast<float>(stof(value.c_str())));
		return true;
	}

	return false;
}

glm::vec2 GameObjectModifierOffset::offset() const
{
	return m_offsetNorm * m_offsetAbs;
}

void GameObjectModifierOffset::setOffset(const glm::vec2& value)
{
	m_offsetAbs = glm::length(value);
	m_offsetNorm = (m_offsetAbs > 0.0001f) ? value / m_offsetAbs : glm::vec2();
}

float GameObjectModifierOffset::velocity() const
{
	return m_offsetVel;
}

void GameObjectModifierOffset::setVelocity(const float value)
{
	m_offsetVel = value;
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
