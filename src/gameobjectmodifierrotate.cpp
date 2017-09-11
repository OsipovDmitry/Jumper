#include "gameobject.h"
#include "gameobjectmodifierrotate.h"
#include "types.h"

void GameObjectModifierRotate::setRotateVelocity(const float value)
{
	m_rotateVel = value;
}

float GameObjectModifierRotate::rotateVelocity() const
{
	return m_rotateVel;
}

GameObjectModifierRotate::GameObjectModifierRotate(GameObject* pObject, float rotateVel) :
	GameObjectAbstractModifier(pObject),
	m_rotateVel(rotateVel)
{
}

GameObjectModifierRotate::~GameObjectModifierRotate()
{
}

void GameObjectModifierRotate::update(uint32_t dt)
{
	m_pGameObject->transform()->angle += m_rotateVel * dt * 0.001f;
}
