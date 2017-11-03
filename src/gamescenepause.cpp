#include <algorithm>

#include "core.h"
#include "gamecontroller.h"
#include "gamescenepause.h"
#include "gameobjectguibutton.h"
#include "gameobjecttext.h"
#include "gameobjectbackground.h"

void GameScenePause::mouseClick(int32_t x, int32_t y)
{
	ObjectsList list = selectObjects(x, y);

	if (std::find(list.cbegin(), list.cend(), m_pResumeButton) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_Level));
	}

	if (std::find(list.cbegin(), list.cend(), m_pRestartButton) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameLoadLevelMessage(m_levelId));
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_Level));
	}

	if (std::find(list.cbegin(), list.cend(), m_pToMenuButton) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_MainMenu));
	}
}

void GameScenePause::activate(GameAbstractScene::AbstractActivateData* pData)
{
	auto pActivateData = dynamic_cast<ActivateData*>(pData);
	assert(pActivateData);
	m_levelId = pActivateData->levelId;
}

GameScenePause::GameScenePause() :
	GameAbstractScene(),
	m_levelId(GameLevelId_None)
{
	m_pBackgroundObject->setBackgroundId(BackgroundId_2);

	auto pText = createGameObject<GameObjectText>("Pause");
	pText->setSize(0.6f);
	pText->setTransform(glm::vec2(0.0f, 0.2f));
	pText->setCentering(0.5f, 0.5f);

	m_pResumeButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Resume);
	m_pResumeButton->setTransform(Transform(glm::vec2(-0.7f, -0.3f)));

	m_pRestartButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Restart);
	m_pRestartButton->setTransform(Transform(glm::vec2(0.0f, -0.3f)));

	m_pToMenuButton = createGameObject<GameObjectGuiButton>(GuiButtonId_ToMenu);
	m_pToMenuButton->setTransform(Transform(glm::vec2(+0.7f, -0.3f)));
}

