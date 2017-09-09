#include "graphicsscene.h"
#include "graphicsobject.h"
#include "gameabstractscene.h"
#include "gameobjectguibutton.h"

void GameObjectGuiButton::setButtonId(GuiButtonId id)
{
	m_pGraphicsObject->setTexture(static_cast<TextureId>(id));
}

GameObjectGuiButton::GameObjectGuiButton(GameAbstractScene *pScene) :
	GameObject(pScene)
{
	static const float height = 0.25f;
	static const float width = 2 * height;

	m_pGraphicsObject = pScene->graphicsScene()->addObject(m_pTransform);
	m_pGraphicsObject->setLayer(LayerId_Gui);
	m_pGraphicsObject->setSize(glm::vec2(width, height));
	m_graphicsObjects.push_back(m_pGraphicsObject);

	setButtonId(GuiButtonId_Start);
}

GameObjectGuiButton::~GameObjectGuiButton()
{

}
