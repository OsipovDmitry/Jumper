#include "glm/common.hpp"

#include "gameobject.h"
#include "gameobjectmodifiertrain.h"

GameObjectModifierTrain::KeyFramesList&GameObjectModifierTrain::keyFramesList()
{
	return m_keyFrames;
}

const GameObjectModifierTrain::KeyFramesList&GameObjectModifierTrain::keyFramesList() const
{
	return m_keyFrames;
}

void GameObjectModifierTrain::setLoop(bool value)
{
	m_isLoop = value;
}

bool GameObjectModifierTrain::isLoop() const
{
	return m_isLoop;
}

GameObjectModifierTrain::GameObjectModifierTrain(GameObject* pObject) :
	GameObjectAbstractModifier(pObject),
	m_keyFrames(),
	m_isLoop(false),
	m_currTime(0.0f)
{

}

GameObjectModifierTrain::~GameObjectModifierTrain()
{

}

void GameObjectModifierTrain::update(uint32_t dt)
{
	assert(!m_keyFrames.empty());

	if (m_keyFrames.size() == 1) {
		m_pGameObject->setTransform(m_keyFrames.front().transform);
		return;
	}

	m_currTime += dt * 0.001f;

	float fullTime = 0.0f;
	for (auto& ref: m_keyFrames)
		fullTime += ref.dtime;

	if (!m_isLoop) {
		if (m_currTime <= m_keyFrames.front().dtime) {
			m_pGameObject->setTransform(m_keyFrames.front().transform);
			return;
		}
		else if (m_currTime >= fullTime) {
			m_pGameObject->setTransform(m_keyFrames.back().transform);
			return;
		}
	}
	else {
		while (m_currTime >= fullTime)
			m_currTime -= fullTime;
	}

	float tempTime = m_currTime;
	for (auto it = m_keyFrames.cbegin(); it != m_keyFrames.cend() - 1; ++it) {
		if (tempTime >= (it+1)->dtime) {
			tempTime -= (it+1)->dtime;
			continue;
		}
		tempTime /= (it+1)->dtime;
		m_pGameObject->setTransform(Transform(glm::mix(it->transform.pos, (it+1)->transform.pos, tempTime),
											  glm::mix(it->transform.angle, (it+1)->transform.angle, tempTime)));
		break;
	}
}
