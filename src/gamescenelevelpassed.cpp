#include <algorithm>

#include "core.h"
#include "gamecontroller.h"
#include "gamescenelevel.h"
#include "gamescenelevelpassed.h"
#include "gameobjecttext.h"
#include "gameobjectbackground.h"
#include "gameobjectguibutton.h"

void GameSceneLevelPassed::mouseClick(int32_t x, int32_t y)
{
	ObjectsList list = selectObjects(x, y);

	if (std::find(list.cbegin(), list.cend(), m_pButtonMenu) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_MainMenu));
	}

	if (std::find(list.cbegin(), list.cend(), m_pButtonRestart) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameLoadLevelMessage(m_passedLevelId));
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_Level));
	}

	if (std::find(list.cbegin(), list.cend(), m_pButtonNext) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameLoadLevelMessage(static_cast<GameLevelId>(m_passedLevelId+1)));
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_Level));
	}
}

void GameSceneLevelPassed::activate(AbstractActivateData *pData)
{
	auto pActivateData = dynamic_cast<ActivateData*>(pData);
	assert(pActivateData);

	m_passedLevelId = pActivateData->levelId;
	auto isNextShow = (m_passedLevelId >= GameLevelId_1) && (m_passedLevelId < GameLevelId_Count-1);
	m_pButtonNext->show(isNextShow);

	if (isNextShow)
		GameSceneLevel::setMaxOpenedLevel(static_cast<GameLevelId>(m_passedLevelId+1));
}

GameSceneLevelPassed::GameSceneLevelPassed() :
	GameAbstractScene(),
	m_passedLevelId(GameLevelId_None)
{
	m_pBackgroundObject->setBackgroundId(BackgroundId_1);

	auto pText = createGameObject<GameObjectText>("Level passed!");
	pText->setSize(0.6f);
	pText->setTransform(glm::vec2(0.0f, 0.2f));
	pText->setCentering(0.5f, 0.5f);

	m_pButtonMenu = createGameObject<GameObjectGuiButton>(GuiButtonId_ToMenu);
	m_pButtonMenu->setTransform(Transform(glm::vec2(-0.3f, -0.3f)));

	m_pButtonRestart = createGameObject<GameObjectGuiButton>(GuiButtonId_Restart);
	m_pButtonRestart->setTransform(Transform(glm::vec2(+0.3f, -0.3f)));

	m_pButtonNext = createGameObject<GameObjectGuiButton>(GuiButtonId_NextLevel);
	m_pButtonNext->setTransform(Transform(glm::vec2(0.0f, -0.6f)));
}
