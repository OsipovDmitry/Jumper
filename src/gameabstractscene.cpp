#include <algorithm>

#include "glm/gtc/matrix_transform.hpp"
#include "types.h"
#include "core.h"
#include "renderwidget.h"
#include "renderer.h"
#include "graphicscontroller.h"
#include "graphicsscene.h"
#include "graphicsobject.h"
#include "physicscontroller.h"
#include "physicsscene.h"
#include "gameobjectbackground.h"
#include "gameabstractscene.h"

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
	m_pObjectBackground(nullptr),
	m_pGraphicsScene(Core::getController<GraphicsController>()->addScene()),
	m_pPhysicsScene(Core::getController<PhysicsController>()->addScene())
{
	m_pObjectBackground = createGameObject<GameObjectBackground>(BackgroundId_0);
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

void GameAbstractScene::mouseClick(int32_t x, int32_t y)
{
	(void)x;
	(void)y;
}

GameAbstractScene::ObjectsList GameAbstractScene::selectObjects(int32_t x, int32_t y)
{
	ObjectsList result;
	for (auto pObject: m_objects) {
		Transform *pObjectTransform = pObject->transform();
		for (auto pGraphicsObject: pObject->m_graphicsObjects) {
			glm::vec2 worldNewPos = glm::vec2(
				glm::rotate(glm::mat4x4(), -pObjectTransform->angle, glm::vec3(0.0f,0.0f,1.0f)) *
				glm::translate(glm::mat4x4(), glm::vec3(-pObjectTransform->pos, 0.0f)) *
				glm::vec4(Core::getController()->renderWidget()->renderer()->windowToWorldSpace(glm::ivec2(x, y), pGraphicsObject->layer()), 0.0f, 1.0f)
			);
			glm::vec2 size = pGraphicsObject->size();
			if ((glm::abs(worldNewPos.x) < size.x) && (glm::abs(worldNewPos.y) < size.y)) {
				result.push_back(pObject);
				continue;
			}
		}
	}

	return std::move(result);
}

void GameAbstractScene::updateScene(uint64_t time, uint32_t dt)
{
	for (auto p: m_objects)
		p->updateObject(dt);

	update(time, dt);
}
