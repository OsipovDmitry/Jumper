#include "glm/gtc/matrix_transform.hpp"

#include "graphicsscene.h"
#include "graphicsobject.h"
#include "physicsscene.h"
#include "physicsgeometry.h"
#include "physicsbody.h"
#include "gameabstractscene.h"
#include "gameobjectbrokenbrick.h"

namespace {
	static const float s_brickHeight = 0.15f;
	static const float s_brickWidth = 3 * s_brickHeight;
}

void GameObjectBrokenBrick::breakDown()
{
	if (!m_isWhole)
		return;

	while (!m_graphicsObjects.empty()) {
		auto p = m_graphicsObjects.front();
		m_graphicsObjects.pop_front();
		m_pScene->graphicsScene()->delObject(p);
	}

	while (!m_physicsBodies.empty()) {
		auto p = m_physicsBodies.front();
		m_physicsBodies.pop_front();
		m_pScene->physicsScene()->delBody(p);
	}

	while (!m_physicsGeoms.empty()) {
		auto p = m_physicsGeoms.front();
		m_physicsGeoms.pop_front();
		m_pScene->physicsScene()->delGeometry(p);
	}

	const int numParts = 4;
	for (int i = 0; i < numParts; ++i) {
		Transform *pTransform = new Transform(m_pTransform->pos, 0.0f);

		auto pGraphicsObject = m_pScene->graphicsScene()->addObject(pTransform);
		pGraphicsObject->setLayer(LayerId_Objects);
		pGraphicsObject->setSize(glm::vec2(s_brickHeight, s_brickHeight));
		pGraphicsObject->setTexture(TextureId_Brick);
		m_graphicsObjects.push_back(pGraphicsObject);

		auto pPhysicsBody = m_pScene->physicsScene()->addBody(pTransform);
		pPhysicsBody->setVelocity(glm::vec2(glm::rotate(glm::mat4x4(), glm::pi<float>() * (1.0f + (float)i/(float)(numParts-1)), glm::vec3(0.0f,0.0f,1.0f))*glm::vec4(1.0f,0.0f,0.0f,1.0f)));
	}

	m_isWhole = true;
}

GameObjectBrokenBrick::GameObjectBrokenBrick(GameAbstractScene *pScene) :
	GameObject(pScene),
	m_isWhole(true)
{
	GraphicsObject *pGraphicsObject = pScene->graphicsScene()->addObject(m_pTransform);
	pGraphicsObject->setLayer(LayerId_Objects);
	pGraphicsObject->setSize(glm::vec2(s_brickWidth, s_brickHeight));
	pGraphicsObject->setTexture(TextureId_Brick);
	m_graphicsObjects.push_back(pGraphicsObject);

	PhysicsGeometry *pPhysicsGeom = pScene->physicsScene()->addStaticBox(m_pTransform, s_brickWidth, s_brickHeight);
	m_physicsGeoms.push_back(pPhysicsGeom);
}

GameObjectBrokenBrick::~GameObjectBrokenBrick()
{

}
