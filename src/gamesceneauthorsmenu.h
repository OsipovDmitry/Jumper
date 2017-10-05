#ifndef GAMESCENEAUTHORSMENU_H
#define GAMESCENEAUTHORSMENU_H

#include "gameabstractscene.h"

class GameObjectGuiButton;

class GameSceneAuthorsMenu : public GameAbstractScene
{
public:

protected:
	void mouseClick(int32_t x, int32_t y);

private:
	GameSceneAuthorsMenu();

	GameObjectGuiButton *m_pBackButton;

	friend class GameController;
};

#endif // GAMESCENEAUTHORSMENU_H
