#ifndef GAMESCENEMAINMENU_H
#define GAMESCENEMAINMENU_H

#include "gameabstractscene.h"

class GameObjectGuiButton;

class GameSceneMainMenu : public GameAbstractScene
{
public:

protected:
	void mouseClick(int32_t x, int32_t y);

private:
	GameSceneMainMenu();

	GameObjectGuiButton *m_pStartButton, *m_pAuthorsButton, *m_pExitButton;

	friend class GameController;
};

#endif // GAMESCENEMAINMENU_H
