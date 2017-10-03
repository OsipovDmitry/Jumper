#include "graphicsobject.h"
#include "graphicscontroller.h"
#include "core.h"
#include "renderwidget.h"
#include "renderer.h"

GraphicsScene *GraphicsObject::scene() const
{
	return m_pScene;
}

const Transform *GraphicsObject::transform() const
{
	return m_pSprite->pTransform;
}

void GraphicsObject::setSize(const glm::vec2& value)
{
	m_pSprite->size = value;
}

glm::vec2 GraphicsObject::size() const
{
	return m_pSprite->size;
}

void GraphicsObject::setTexture(TextureId texId)
{
	m_pSprite->textureId = texId;
}

TextureId GraphicsObject::texture() const
{
	return m_pSprite->textureId;
}

void GraphicsObject::setLayer(LayerId value)
{
	m_pSprite->layerId = value;
}

LayerId GraphicsObject::layer() const
{
	return m_pSprite->layerId;
}

void GraphicsObject::setOpacity(float value)
{
	m_pSprite->opacity = value;
}

float GraphicsObject::opacity() const
{
	return m_pSprite->opacity;
}

void GraphicsObject::setVisible(bool state)
{
	m_pSprite->visible = state;
}

bool GraphicsObject::isVisible() const
{
	return m_pSprite->visible;
}

GraphicsObject::GraphicsObject(GraphicsScene* pScene, const Transform* pTransform) :
	m_pScene(pScene)
{
	Renderer *pRenderer = Core::getController()->renderWidget()->renderer();
	m_pSprite = pRenderer->createSprite(pTransform);
	if (Core::getController<GraphicsController>()->currentScene() == pScene)
		pRenderer->drawSprite(m_pSprite);
}

GraphicsObject::~GraphicsObject()
{
	Core::getController()->renderWidget()->renderer()->destroySprite(m_pSprite);
}
