#include "core.h"
#include "graphicsscene.h"
#include "graphicsobject.h"
#include "physicsscene.h"
#include "physicsgeometry.h"
#include "audiocontroller.h"
#include "gameabstractscene.h"
#include "gameobjectbrick.h"

void GameObjectBrick::use()
{
	Core::getController<AudioController>()->playSound(SoundId_Jump, m_pTransform);
}

GameObjectBrick::GameObjectBrick(GameAbstractScene* pScene) :
	GameObject(pScene, typeOfClass())
{
	static const float height = 0.15f;
	static const float width = 3 * height;

	auto pGraphicsObject = pScene->graphicsScene()->addObject(m_pTransform);
	pGraphicsObject->setLayer(LayerId_Objects);
	pGraphicsObject->setSize(glm::vec2(width, height));
	pGraphicsObject->setTexture(TextureId_Brick);
	m_graphicsObjects.push_back(pGraphicsObject);

	auto pPhysicsGeom = pScene->physicsScene()->addStaticBox(m_pTransform, width, height);
	pPhysicsGeom->setData(static_cast<void*>(this));
	m_physicsGeoms.push_back(pPhysicsGeom);
}

GameObjectBrick::~GameObjectBrick()
{
}
