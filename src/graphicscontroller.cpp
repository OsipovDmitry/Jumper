#include <algorithm>
#include <cassert>

#include "graphicscontroller.h"
#include "graphicsscene.h"

GraphicsScene *GraphicsController::addScene()
{
	GraphicsScene *pScene = new GraphicsScene;
	m_scenes.push_back(pScene);
	return pScene;
}

void GraphicsController::delScene(GraphicsScene* pScene)
{	
	ScenesList::iterator it = std::find(m_scenes.begin(), m_scenes.end(), pScene);
	assert(it != m_scenes.end());

	if (m_pCurrentScene == pScene)
		setCurrentScene(nullptr);

	m_scenes.erase(it);
	delete pScene;
}

GraphicsScene *GraphicsController::currentScene()
{
	return m_pCurrentScene;
}

void GraphicsController::setCurrentScene(GraphicsScene* pScene)
{
	if (m_pCurrentScene)
		m_pCurrentScene->hide();
	m_pCurrentScene = pScene;
	if (m_pCurrentScene)
		m_pCurrentScene->show();

}

bool GraphicsController::process(AbstractControllerMessage* pMessage)
{
	switch (pMessage->type()) {
	case CMT_ControllerInit: {
		auto pMsg = msg_cast<ControllerInitMessage>(pMessage);
		if (pMsg) {
			//
		}
		return true;
	}
	case CMT_ControllerUpdate: {
		auto pMsg = msg_cast<ControllerUpdateMessage>(pMessage);
		if (pMsg)
			update(pMsg->dt);
		return true;
	}
	default: break;
	}
	return false;
}

GraphicsController::GraphicsController() :
	AbstractController(),
	m_scenes(),
	m_pCurrentScene(nullptr)
{
}

GraphicsController::~GraphicsController()
{
	for (auto p: m_scenes)
		delete p;

	m_scenes.clear();
}

void GraphicsController::update(uint32_t dt)
{
	if (m_pCurrentScene)
		m_pCurrentScene->update(dt);
}
