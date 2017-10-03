#include <algorithm>

#include "types.h"
#include "core.h"
#include "gamecontroller.h"
#include "gameobjectbackground.h"
#include "gameobjecttext.h"
#include "gameobjectguibutton.h"
#include "gamesceneauthorsmenu.h"
#include "gameobjectmodifierrotate.h"


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

	auto p = createGameObject<GameObjectText>("Jumper");
	p->setTransform(glm::vec2(0.0f, 0.8f));
	p->setCentering(0.5f, 0.0f);

	p = createGameObject<GameObjectText>("Test game");
	p->setTransform(glm::vec2(0.0f, 0.6f));
	p->setCentering(0.5f, 0.0f);

	p = createGameObject<GameObjectText>("Dmitry Osipov\n"
										 "dmitry1992osipov@yandex.ru");
	p->setTransform(glm::vec2(0.0f, 0.4f));
	p->setCentering(0.5f, 0.0f);

}

GameSceneAuthorsMenu::~GameSceneAuthorsMenu()
{

}
