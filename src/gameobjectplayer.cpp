#include "graphicsscene.h"
#include "graphicsobject.h"
#include "physicsscene.h"
#include "physicsgeometry.h"
#include "physicsbody.h"
#include "gameabstractscene.h"
#include "gameobjectplayer.h"

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
