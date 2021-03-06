#include <algorithm>

#include "types.h"
#include "mathutils.h"
#include "core.h"
#include "renderwidget.h"
#include "renderer.h"
#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsobject.h"
#include "physicscontroller.h"
#include "physicsscene.h"
#include "physicsgeometry.h"
#include "gamecontroller.h"
#include "gameabstractscene.h"
#include "gameobjectbackground.h"

GraphicsScene *GameAbstractScene::graphicsScene() const
{
	return m_pGraphicsScene;
}

PhysicsScene *GameAbstractScene::physicsScene() const
{
	return m_pPhysicsScene;
}

GameAbstractScene::GameAbstractScene() :
	m_objects(),
	m_pGraphicsScene(Core::getController<GraphicsController>()->addScene()),
	m_pPhysicsScene(Core::getController<PhysicsController>()->addScene())
{
	m_pPhysicsScene->setCollisionDetectionCallback(collisionDetection, static_cast<void*>(this));

	m_pBackgroundObject = createGameObject<GameObjectBackground>(BackgroundId_0);
}

GameAbstractScene::~GameAbstractScene()
{
	while (!m_objects.empty())
		delGameObject(m_objects.front());

	Core::getController<GraphicsController>()->delScene(m_pGraphicsScene);
	Core::getController<PhysicsController>()->delScene(m_pPhysicsScene);
}

void GameAbstractScene::delGameObject(GameObject* pObject)
{
	assert(pObject->scene() == this);

	auto it = std::find(m_objects.begin(), m_objects.end(), pObject);
	assert(it != m_objects.end());

	for (auto p: pObject->m_graphicsObjects)
		m_pGraphicsScene->delObject(p);

	for (auto p: pObject->m_physicsBodies)
		m_pPhysicsScene->delBody(p);

	for (auto p: pObject->m_physicsGeoms)
		m_pPhysicsScene->delGeometry(p);

	m_objects.erase(it);
	delete pObject;
}

GameAbstractScene::ObjectsList GameAbstractScene::selectObjects(int32_t x, int32_t y)
{
	auto pRenderer = Core::getController()->renderWidget()->renderer();
	ObjectsList result;
	for (auto pObject: m_objects) {
		for (auto pGraphicsObject: pObject->m_graphicsObjects) {
			if (!pGraphicsObject->isVisible())
				continue;
			glm::vec2 worldPos = pRenderer->windowToWorldSpace(glm::ivec2(x, y), pGraphicsObject->layer());
			glm::vec2 localPos = toLocalSpace(pObject->m_pTransform, worldPos);
			glm::vec2 halfSize = 0.5f * pGraphicsObject->size();

			if ((glm::abs(localPos.x) < halfSize.x) && (glm::abs(localPos.y) < halfSize.y))
				result.push_back(pObject);
		}
	}

	return result;
}

void GameAbstractScene::updateScene(uint32_t dt)
{
	for (auto p: m_objects)
		p->updateObject(dt);

	update(dt);
}

void GameAbstractScene::collisionDetection(PhysicsGeometry* p1, PhysicsGeometry* p2)
{
	auto pGameObject1 = static_cast<GameObject*>(p1->data());
	auto pGameObject2 = static_cast<GameObject*>(p2->data());

	if (pGameObject1)
		Core::getController<GameController>()->sendMessage(new GameObjectUseMessage(pGameObject1, pGameObject2));

	if (pGameObject2)
		Core::getController<GameController>()->sendMessage(new GameObjectUseMessage(pGameObject2, pGameObject1));
}

void GameAbstractScene::collisionDetection(void *pSceneData, PhysicsGeometry* p1, PhysicsGeometry* p2)
{
	static_cast<GameAbstractScene*>(pSceneData)->collisionDetection(p1, p2);
}
