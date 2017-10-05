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
	m_pBackgroundObject(nullptr),
	m_pGraphicsScene(Core::getController<GraphicsController>()->addScene()),
	m_pPhysicsScene(Core::getController<PhysicsController>()->addScene())
{
	m_pPhysicsScene->setCollisionDetectionCallback(collisionDetection, static_cast<void*>(this));

	m_pBackgroundObject = createGameObject<GameObjectBackground>(BackgroundId_0);
}

GameAbstractScene::~GameAbstractScene()
{
	while (!m_objects.empty())
		delObject(m_objects.front());

	Core::getController<GraphicsController>()->delScene(m_pGraphicsScene);
	Core::getController<PhysicsController>()->delScene(m_pPhysicsScene);
}

void GameAbstractScene::delObject(GameObject* pObject)
{
	assert(pObject->scene() == this);

	auto it = std::find(m_objects.begin(), m_objects.end(), pObject);
	assert(it != m_objects.end());

	std::for_each(pObject->m_graphicsObjects.begin(), pObject->m_graphicsObjects.end(), [this](GraphicsObject *p){
		this->m_pGraphicsScene->delObject(p);
	});

	std::for_each(pObject->m_physicsBodies.begin(), pObject->m_physicsBodies.end(), [this](PhysicsBody *p){
		this->m_pPhysicsScene->delBody(p);
	});

	std::for_each(pObject->m_physicsGeoms.begin(), pObject->m_physicsGeoms.end(), [this](PhysicsGeometry *p){
		this->m_pPhysicsScene->delGeometry(p);
	});

	m_objects.erase(it);
	delete pObject;
}



GameAbstractScene::ObjectsList GameAbstractScene::selectObjects(int32_t x, int32_t y)
{
	Renderer *pRenderer = Core::getController()->renderWidget()->renderer();
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

void GameAbstractScene::updateScene(uint64_t time, uint32_t dt)
{
	for (auto p: m_objects)
		p->updateObject(dt);

	update(time, dt);
}

void GameAbstractScene::collisionDetection(PhysicsGeometry* p1, PhysicsGeometry* p2)
{
	auto pGameObject = static_cast<GameObject*>(p1->data());
	if (pGameObject)
		Core::getController<GameController>()->sendMessage(new GameObjectUseMessage(pGameObject));

	pGameObject = static_cast<GameObject*>(p2->data());
	if (pGameObject)
		Core::getController<GameController>()->sendMessage(new GameObjectUseMessage(pGameObject));
}

void GameAbstractScene::collisionDetection(void *pSceneData, PhysicsGeometry* p1, PhysicsGeometry* p2)
{
	static_cast<GameAbstractScene*>(pSceneData)->collisionDetection(p1, p2);
}
