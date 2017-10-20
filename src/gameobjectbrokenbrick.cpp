#include "glm/gtc/matrix_transform.hpp"

#include "core.h"
#include "graphicsscene.h"
#include "graphicsobject.h"
#include "physicsscene.h"
#include "physicsgeometry.h"
#include "physicsbody.h"
#include "audiocontroller.h"
#include "gameabstractscene.h"
#include "gameobjectbrokenbrick.h"
#include "mathutils.h"

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

	const int numParts = 3 + rand() % 3;
	const float partsStartVel = 1.8f;
	for (int i = 0; i < numParts; ++i) {
		Part *pPart = new Part;

		pPart->pTransform = new Transform(
								toWorldSpace(m_pTransform, glm::vec2(s_brickWidth*((float)i/(float)(numParts-1)-0.5f), 0.0f)),
								rand(0.0f, glm::two_pi<float>())
								);

		pPart->pGraphicsObject = m_pScene->graphicsScene()->addObject(pPart->pTransform);
		pPart->pGraphicsObject->setLayer(LayerId_Objects);
		pPart->pGraphicsObject->setSize(glm::vec2(s_brickHeight, s_brickHeight));
		pPart->pGraphicsObject->setTexture(TextureId_BrockenBrickPart);

		pPart->pPhysicsBody = m_pScene->physicsScene()->addBody(pPart->pTransform);
		pPart->pPhysicsBody->setVelocity(partsStartVel * glm::vec2(glm::rotate(glm::mat4x4(), glm::pi<float>() * (1.0f + (float)i/(float)(numParts-1)), glm::vec3(0.0f,0.0f,1.0f))*glm::vec4(1.0f,0.0f,0.0f,1.0f)));

		m_parts.push_back(pPart);
	}

	m_isWhole = false;

	Core::getController<AudioController>()->playSound(SoundId_BrokenJump, m_pTransform);
}

GameObjectBrokenBrick::GameObjectBrokenBrick(GameAbstractScene *pScene) :
	GameObject(pScene),
	m_parts(),
	m_isWhole(true)
{
	auto pGraphicsObject = pScene->graphicsScene()->addObject(m_pTransform);
	pGraphicsObject->setLayer(LayerId_Objects);
	pGraphicsObject->setSize(glm::vec2(s_brickWidth, s_brickHeight));
	pGraphicsObject->setTexture(TextureId_BrokenBrick);
	m_graphicsObjects.push_back(pGraphicsObject);

	auto pPhysicsGeom = pScene->physicsScene()->addStaticBox(m_pTransform, s_brickWidth, s_brickHeight);
	pPhysicsGeom->setData(static_cast<void*>(this));
	m_physicsGeoms.push_back(pPhysicsGeom);
}

GameObjectBrokenBrick::~GameObjectBrokenBrick()
{
	for (auto pPart: m_parts) {
		m_pScene->graphicsScene()->delObject(pPart->pGraphicsObject);
		m_pScene->physicsScene()->delBody(pPart->pPhysicsBody);
		delete pPart->pTransform;
		delete pPart;
	}
	m_parts.clear();
}

void GameObjectBrokenBrick::update(uint32_t dt)
{
	(void)dt;
	if (m_isWhole)
		return;

	PartsList fallenParts;
	for (auto pPart: m_parts) {
		if (pPart->pTransform->pos.y < GLOBAL_DOWN)
			fallenParts.push_back(pPart);
	}
	for (auto pPart: fallenParts) {
		m_pScene->graphicsScene()->delObject(pPart->pGraphicsObject);
		m_pScene->physicsScene()->delBody(pPart->pPhysicsBody);
		delete pPart->pTransform;
		m_parts.remove(pPart);
		delete pPart;
	}
}

void GameObjectBrokenBrick::use()
{
	breakDown();
}
