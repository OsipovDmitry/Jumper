#include <algorithm>

#include "graphicsscene.h"
#include "graphicsobject.h"
#include "graphicscamera.h"
#include "core.h"
#include "renderwidget.h"
#include "renderer.h"

GraphicsObject *GraphicsScene::addObject(const Transform* pTransform)
{
	GraphicsObject *pObject = new GraphicsObject(this, pTransform);
	m_objects.push_back(pObject);
	return pObject;
}

void GraphicsScene::delObject(GraphicsObject* pObject)
{
	assert(pObject->scene() == this);

	ObjectsList::iterator it = std::find(m_objects.begin(), m_objects.end(), pObject);
	assert(it != m_objects.end());

	m_objects.erase(it);
	delete pObject;
}

GraphicsCamera *GraphicsScene::camera() const
{
	return m_pCamera;
}

GraphicsScene::GraphicsScene() :
	m_objects(),
	m_pCamera(new GraphicsCamera)
{
}

GraphicsScene::~GraphicsScene()
{
	while (!m_objects.empty())
		delObject(m_objects.front());

	delete m_pCamera;
}

void GraphicsScene::show()
{
	for (ObjectsList::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
		(*it)->setVisible(true);
	Core::getController()->renderWidget()->renderer()->setCameraTransform(m_pCamera->transform());
}

void GraphicsScene::hide()
{
	for (ObjectsList::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
		(*it)->setVisible(false);
}
