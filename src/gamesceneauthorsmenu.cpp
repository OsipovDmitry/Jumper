#include <algorithm>

#include "types.h"
#include "core.h"
#include "gamecontroller.h"
#include "gameobjectbackground.h"
#include "gameobjecttext.h"
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
    m_pBackgroundObject->setBackgroundId(BackgroundId_1);

	m_pBackButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Back);
	m_pBackButton->setTransform(Transform(glm::vec2(0.0f, -0.6f)));

    auto p = createGameObject<GameObjectText>("Abc def Dima\n123\t456\n!@#$%^&*()_+");
	p->setTransform(Transform(glm::vec2(-1, 0.5), 0.25f * 3.1415f));
	p->setCentering(0.5f, 0.0f);
}

GameSceneAuthorsMenu::~GameSceneAuthorsMenu()
{

}
