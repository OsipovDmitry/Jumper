#include <algorithm>

#include "types.h"
#include "core.h"
#include "gamecontroller.h"
#include "gamescenelevel.h"
#include "gamesceneselectlevel.h"
#include "gameobjectbackground.h"
#include "gameobjectguibutton.h"

void GameSceneSelectLevel::mouseClick(int32_t x, int32_t y)
{
	ObjectsList list = selectObjects(x, y);

	for (auto id = GameLevelId_1; id < GameLevelId_Count; id = static_cast<GameLevelId>(id+1)) {
		if (std::find(list.cbegin(), list.cend(), m_pLevelButton[id]) != list.cend()) {
			Core::getController<GameController>()->sendMessage(new GameLoadLevelMessage(id));
			Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_Level));
		}
	}

	if (std::find(list.cbegin(), list.cend(), m_pBackButton) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_MainMenu));
	}
}

void GameSceneSelectLevel::activate(AbstractActivateData*)
{
	for (auto id = GameLevelId_1; id < GameLevelId_Count; id = static_cast<GameLevelId>(id+1))
		m_pLevelButton[id]->show();

	auto maxLevel = GameSceneLevel::maxOpenedLevel();
	for (auto id = GameLevelId_Count-1; id >= GameLevelId_1; id = static_cast<GameLevelId>(id-1)) {
		if (maxLevel < id)
			m_pLevelButton[id]->hide();
		else {
			for (auto i = GameLevelId_1; i <= id; i = static_cast<GameLevelId>(i+1))
				m_pLevelButton[i]->setTransform(Transform(glm::vec2(0.7f * (i - 0.5f*id), 0.2f)));
			break;
		}
	}
}

GameSceneSelectLevel::GameSceneSelectLevel() :
	GameAbstractScene()
{
	m_pBackgroundObject->setBackgroundId(BackgroundId_0);

	for (auto id = GameLevelId_1; id < GameLevelId_Count; id = static_cast<GameLevelId>(id+1)) {
		m_pLevelButton[id] = createGameObject<GameObjectGuiButton>(static_cast<GuiButtonId>(GuiButtonId_Level1 + static_cast<int>(id)));
	}

	m_pBackButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Back);
	m_pBackButton->setTransform(Transform(glm::vec2(0.0f, -0.6f)));
}

GameSceneSelectLevel::~GameSceneSelectLevel()
{
}
