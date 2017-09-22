#include <algorithm>

#include "core.h"
#include "gamescenemainmenu.h"
#include "gameobjectguibutton.h"

void GameSceneMainMenu::mouseClick(int32_t x, int32_t y)
{
	ObjectsList list = selectObjects(x, y);

//	if (std::find(list.cbegin(), list.cend(), m_pButtonStart) != list.cend()) {
//		m_pPlayer->setTransform(Transform(glm::vec2(0.0f, 0.7f), 0.0f));
//		m_pPlayer->physicsBody()->setVelocity(glm::vec2(0.0f, 0.0f));
//	}

	if (std::find(list.cbegin(), list.cend(), m_pExitButton) != list.cend()) {
		Core::getController()->sendMessage(new CoreExitMessage());
	}
}

GameSceneMainMenu::GameSceneMainMenu()
{
	m_pStartButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Start);
	m_pStartButton->setTransform(Transform(glm::vec2(0.0f, 0.3f), 0.0f));

	m_pAuthorsButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Empty);
	m_pAuthorsButton->setTransform(Transform(glm::vec2(0.0f, 0.0f), 0.0f));

	m_pExitButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Exit);
	m_pExitButton->setTransform(Transform(glm::vec2(0.0f, -0.3f), 0.0f));
}

GameSceneMainMenu::~GameSceneMainMenu()
{

}
