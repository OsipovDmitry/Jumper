#include "graphicsscene.h"
#include "graphicsobject.h"
#include "physicsscene.h"
#include "physicsgeometry.h"
#include "gameabstractscene.h"
#include "gameobjectbrick.h"

GameObjectBrick::GameObjectBrick(GameAbstractScene* pScene) :
	GameObject(pScene)
{
	static const float height = 0.15f;
	static const float width = 3 * height;

	GraphicsObject *pGraphicsObject = pScene->graphicsScene()->addObject(m_pTransform);
	pGraphicsObject->setLayer(LayerId_Objects);
	pGraphicsObject->setSize(glm::vec2(width, height));
	pGraphicsObject->setTexture(TextureId_Brick);
	m_graphicsObjects.push_back(pGraphicsObject);

	PhysicsGeometry *pPhysicsGeom = pScene->physicsScene()->addStaticBox(m_pTransform, width, height);
	m_physicsGeoms.push_back(pPhysicsGeom);
}

GameObjectBrick::~GameObjectBrick()
{
}
