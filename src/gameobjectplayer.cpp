#include "graphicsscene.h"
#include "graphicsobject.h"
#include "physicsscene.h"
#include "physicsgeometry.h"
#include "physicsbody.h"
#include "gameabstractscene.h"
#include "gameobjectplayer.h"

void GameObjectPlayer::update(uint32_t dt)
{
	(void)dt;
//	static const float  coef = 0.5f;
//	PhysicsBody *pBody = m_physicsBodies.front();
//	glm::vec2 vel = pBody->velocity();
//	float len = glm::length(vel);
//	vel = (len > 0.0001f) ? vel /= len : glm::vec2();
//	len -= coef * dt * 0.001f;
	//	pBody->setVelocity(vel * len);
}

PhysicsBody *GameObjectPlayer::physicsBody() const
{
	return m_physicsBodies.front();
}

GameObjectPlayer::GameObjectPlayer(GameAbstractScene* pScene) :
	GameObject(pScene)
{
	static const float ballRadius = 0.125f;

	auto *pGraphicsObject = pScene->graphicsScene()->addObject(m_pTransform);
	pGraphicsObject->setLayer(LayerId_Objects);
	pGraphicsObject->setSize(glm::vec2(2*ballRadius, 2*ballRadius));
	pGraphicsObject->setTexture(TextureId_Circle);
	m_graphicsObjects.push_back(pGraphicsObject);

	auto *pPhysicsBody = pScene->physicsScene()->addBody(m_pTransform);
	m_physicsBodies.push_back(pPhysicsBody);

	auto *pPhysicsGeom = pScene->physicsScene()->addDynamicSphere(pPhysicsBody, ballRadius);
	m_physicsGeoms.push_back(pPhysicsGeom);
}

GameObjectPlayer::~GameObjectPlayer()
{

}
