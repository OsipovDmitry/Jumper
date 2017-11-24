#include <unordered_map>

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

bool GameObjectBackground::setParam(const std::string& key, const std::string& value)
{
	if (GameObject::setParam(key, value))
		return true;

	static const std::string s_idTag = "id";

	if (key == s_idTag) {
		setBackgroundId(paramToBackgroundId(value));
		return true;
	}

	return false;
}

GameObjectBackground::GameObjectBackground(GameAbstractScene *pScene, BackgroundId id) :
	GameObject(pScene, typeOfClass())
{
	m_pGraphicsObject = pScene->graphicsScene()->addObject(m_pTransform);
	m_pGraphicsObject->setLayer(LayerId_Background);
	m_pGraphicsObject->setSize(glm::vec2(2.0f, 2.0f));
	m_graphicsObjects.push_back(m_pGraphicsObject);

	setBackgroundId(id);
}

GameObjectBackground::~GameObjectBackground()
{
}

BackgroundId GameObjectBackground::paramToBackgroundId(const std::string& param)
{
	static const std::unordered_map<std::string, BackgroundId> table = {
		{"0", BackgroundId_0},
		{"1", BackgroundId_1},
		{"2", BackgroundId_2},
		{"3", BackgroundId_3},
	};

	auto it = table.find(param);
	return (it != table.end()) ? it->second : BackgroundId_0;
}
