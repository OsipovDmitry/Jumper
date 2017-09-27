#include <unordered_map>

#include "graphicsscene.h"
#include "graphicsobject.h"
#include "gameabstractscene.h"
#include "gameobjectguibutton.h"

void GameObjectGuiButton::setButtonId(GuiButtonId id)
{
	m_pGraphicsObject->setTexture(static_cast<TextureId>(id));
}

bool GameObjectGuiButton::setParam(const std::__cxx11::string& key, const std::__cxx11::string& value)
{
	if (GameObject::setParam(key, value))
		return true;

	static const std::string s_idTag = "id";

	if (key == s_idTag) {
		setButtonId(paramToButtonId(value));
		return true;
	}

	return false;
}

GameObjectGuiButton::GameObjectGuiButton(GameAbstractScene *pScene, GuiButtonId id) :
	GameObject(pScene)
{
	static const float height = 0.25f;
	static const float width = 2 * height;

	m_pGraphicsObject = pScene->graphicsScene()->addObject(m_pTransform);
	m_pGraphicsObject->setLayer(LayerId_Gui);
	m_pGraphicsObject->setSize(glm::vec2(width, height));
	m_graphicsObjects.push_back(m_pGraphicsObject);

	setButtonId(id);
}

GameObjectGuiButton::~GameObjectGuiButton()
{

}

GuiButtonId GameObjectGuiButton::paramToButtonId(const std::string& param)
{
	static const std::unordered_map<std::string, GuiButtonId> table = {
		{"start", GuiButtonId_Start},
		{"exit", GuiButtonId_Exit},
		{"empty", GuiButtonId_Empty},
		{"authors", GuiButtonId_Authors},
		{"back", GuiButtonId_Back},
		{"level1", GuiButtonId_Level1},
		{"level2", GuiButtonId_Level2},
		{"level3", GuiButtonId_Level3},
	};

	auto it = table.find(param);
	return (it != table.end()) ? it->second : GuiButtonId_Empty;
}
