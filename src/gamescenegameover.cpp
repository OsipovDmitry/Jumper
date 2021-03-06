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
		Core::getController<GameController>()->sendMessage(new GameLoadLevelMessage(m_overLevelId));
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_Level));
	}
}

void GameSceneGameOver::activate(GameAbstractScene::AbstractActivateData* pData)
{
	auto pActivateData = dynamic_cast<ActivateData*>(pData);
	assert(pActivateData);
	m_overLevelId = pActivateData->levelId;
}

GameSceneGameOver::GameSceneGameOver() :
	GameAbstractScene(),
	m_overLevelId(GameLevelId_None)
{
	m_pBackgroundObject->setBackgroundId(BackgroundId_1);

	auto pText = createGameObject<GameObjectText>("Game over!");
	pText->setSize(0.6f);
	pText->setTransform(glm::vec2(0.0f, 0.2f));
	pText->setCentering(0.5f, 0.5f);

	m_pButtonMenu = createGameObject<GameObjectGuiButton>(GuiButtonId_ToMenu);
	m_pButtonMenu->setTransform(Transform(glm::vec2(-0.3f, -0.3f)));

	m_pButtonRestart = createGameObject<GameObjectGuiButton>(GuiButtonId_Restart);
	m_pButtonRestart->setTransform(Transform(glm::vec2(+0.3f, -0.3f)));
}

GameSceneGameOver::~GameSceneGameOver()
{

}
