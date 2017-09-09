#include <algorithm>
#include <cassert>

#include "physicscontroller.h"
#include "physicsscene.h"

PhysicsScene *PhysicsController::addScene()
{
	PhysicsScene *pScene = new PhysicsScene;
	m_scenes.push_back(pScene);
	return pScene;
}

void PhysicsController::delScene(PhysicsScene* pScene)
{
	ScenesList::iterator it = std::find(m_scenes.begin(), m_scenes.end(), pScene);
	assert(it != m_scenes.end());

	if (m_pCurrentScene == pScene)
		setCurrentScene(nullptr);

	m_scenes.erase(it);
	delete pScene;
}

PhysicsScene *PhysicsController::currentScene()
{
	return m_pCurrentScene;
}

void PhysicsController::setCurrentScene(PhysicsScene* pScene)
{
	m_pCurrentScene = pScene;
}

bool PhysicsController::process(AbstractControllerMessage* pMessage)
{
	switch (pMessage->type()) {
	case CMT_ControllerUpdate: {
		ControllerUpdateMessage *pMsg = msg_cast<ControllerUpdateMessage>(pMessage);
		if (pMsg)
			update(pMsg->dt);
		break;
	}
	default: break;
	}
}

PhysicsController::PhysicsController() :
	AbstractController(),
	m_scenes(),
	m_pCurrentScene(nullptr)
{

}

PhysicsController::~PhysicsController()
{
	for (ScenesList::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
		delete (*it);
	m_scenes.clear();
}

void PhysicsController::update(uint32_t dt)
{
	if (m_pCurrentScene)
		m_pCurrentScene->update(dt);
}
