#include "core.h"
#include "graphicsscene.h"
#include "graphicsobject.h"
#include "physicsscene.h"
#include "physicsgeometry.h"
#include "audiocontroller.h"
#include "gamecontroller.h"
#include "gameabstractscene.h"
#include "gamescenelevelpassed.h"
#include "gameobjectlevelpassed.h"

void GameObjectLevelPassed::use()
{
	Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_LevelPassed, new GameSceneLevelPassed::ActivateData(m_levelId)));
	Core::getController<AudioController>()->playSound(SoundId_LevelPassed, nullptr);
}

GameObjectLevelPassed::GameObjectLevelPassed(GameAbstractScene* pScene, GameLevelId id) :
	GameObject(pScene),
	m_levelId(id)
{
	static const float height = 0.4f;
	static const float width = 1.5f * height;

	auto pGraphicsObject = pScene->graphicsScene()->addObject(m_pTransform);
	pGraphicsObject->setLayer(LayerId_Objects);
	pGraphicsObject->setSize(glm::vec2(width, height));
	pGraphicsObject->setTexture(TextureID_LevelPassed);
	m_graphicsObjects.push_back(pGraphicsObject);

	auto pPhysicsGeom = pScene->physicsScene()->addStaticBox(m_pTransform, 0.5f * width, 0.5f * height);
	pPhysicsGeom->setData(static_cast<void*>(this));
	m_physicsGeoms.push_back(pPhysicsGeom);
}
