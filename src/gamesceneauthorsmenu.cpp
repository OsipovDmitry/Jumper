#include <algorithm>

#include "types.h"
#include "core.h"
#include "gamecontroller.h"
#include "gameobjectguibutton.h"
#include "gamesceneauthorsmenu.h"


void GameSceneAuthorsMenu::mouseClick(int32_t x, int32_t y)
{
	ObjectsList list = selectObjects(x, y);

	if (std::find(list.cbegin(), list.cend(), m_pBackButton) != list.cend()) {
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_MainMenu));
	}
}

GameSceneAuthorsMenu::GameSceneAuthorsMenu() :
	GameAbstractScene()
{
	m_pBackButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Back);
	m_pBackButton->setTransform(Transform(glm::vec2(0.0f, -0.6f)));
}

GameSceneAuthorsMenu::~GameSceneAuthorsMenu()
{

}
