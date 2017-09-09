#include "graphicsscene.h"
#include "graphicsobject.h"
#include "gameabstractscene.h"
#include "gameobjectbackground.h"

void GameObjectBackground::setBackgroundId(BackgroundId id)
{
	m_pGraphicsObject->setTexture(static_cast<TextureId>(id));
}

BackgroundId GameObjectBackground::backgrounId() const
{
	return static_cast<BackgroundId>(m_pGraphicsObject->texture());
}

GameObjectBackground::GameObjectBackground(GameAbstractScene *pScene) :
	GameObject(pScene)
{
	m_pGraphicsObject = pScene->graphicsScene()->addObject(m_pTransform);
	m_pGraphicsObject->setLayer(LayerId_Background);
	m_pGraphicsObject->setSize(glm::vec2(2.0f, 2.0f));
	m_graphicsObjects.push_back(m_pGraphicsObject);

	setBackgroundId(BackgroundId_0);
}

GameObjectBackground::~GameObjectBackground()
{
}
