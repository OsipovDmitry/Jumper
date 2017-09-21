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
	case CMT_ControllerUpdate: {
		ControllerUpdateMessage *pMsg = msg_cast<ControllerUpdateMessage>(pMessage);
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
	for (ScenesList::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
		delete (*it);
	m_scenes.clear();
}

void GraphicsController::update(uint32_t dt)
{
	(void)dt;
}
