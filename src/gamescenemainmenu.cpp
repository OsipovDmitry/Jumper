#include <algorithm>

#include "core.h"
#include "gamecontroller.h"
#include "gamescenemainmenu.h"
#include "gameobjectguibutton.h"

void GameSceneMainMenu::mouseClick(int32_t x, int32_t y)
{
	ObjectsList list = selectObjects(x, y);

	if (std::find(list.cbegin(), list.cend(), m_pStartButton) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_Level));
	}

	if (std::find(list.cbegin(), list.cend(), m_pAuthorsButton) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_Authors));
	}

	if (std::find(list.cbegin(), list.cend(), m_pExitButton) != list.cend()) {
		Core::getController()->sendMessage(new CoreExitMessage());
	}
}

GameSceneMainMenu::GameSceneMainMenu()
{
	m_pStartButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Start);
	m_pStartButton->setTransform(Transform(glm::vec2(0.0f, 0.3f)));

	m_pAuthorsButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Authors);
	m_pAuthorsButton->setTransform(Transform(glm::vec2(0.0f, 0.0f)));

	m_pExitButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Exit);
	m_pExitButton->setTransform(Transform(glm::vec2(0.0f, -0.3f)));
}

GameSceneMainMenu::~GameSceneMainMenu()
{
	delObject(m_pStartButton);
	delObject(m_pAuthorsButton);
	delObject(m_pExitButton);
}
