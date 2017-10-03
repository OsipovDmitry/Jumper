#include <algorithm>

#include "core.h"
#include "gamecontroller.h"
#include "gamescenegameover.h"
#include "gameobjecttext.h"
#include "gameobjectbackground.h"
#include "gameobjectguibutton.h"

void GameSceneGameOver::mouseClick(int32_t x, int32_t y)
{
	ObjectsList list = selectObjects(x, y);

	if (std::find(list.cbegin(), list.cend(), m_pButtonMenu) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_MainMenu));
	}

	if (std::find(list.cbegin(), list.cend(), m_pButtonRestart) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameReloadLevelMessage());
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_Level));
	}
}

GameSceneGameOver::GameSceneGameOver() :
	GameAbstractScene()
{
	m_pBackgroundObject->setBackgroundId(BackgroundId_1);
	auto pText = createGameObject<GameObjectText>("Game Over!");
	pText->setSize(0.5f);
	pText->setTransform(glm::vec2(0.0f, 0.2f));
	pText->setCentering(0.5f, 0.5f);

	m_pButtonMenu = createGameObject<GameObjectGuiButton>(GuiButtonId_Empty);
	m_pButtonMenu->setTransform(Transform(glm::vec2(-0.3f, -0.2f)));

	m_pButtonRestart = createGameObject<GameObjectGuiButton>(GuiButtonId_Empty);
	m_pButtonRestart->setTransform(Transform(glm::vec2(+0.3f, -0.2f)));
}

GameSceneGameOver::~GameSceneGameOver()
{

}
