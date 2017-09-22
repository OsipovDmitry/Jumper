#ifndef GAMESCENEMAINMENU_H
#define GAMESCENEMAINMENU_H

#include "gameabstractscene.h"

class GameObjectGuiButton;

class GameSceneMainMenu : public GameAbstractScene
{
public:

protected:
	//void update(uint64_t time, uint32_t dt);
	void mouseClick(int32_t x, int32_t y);

private:
	GameSceneMainMenu();
	~GameSceneMainMenu();

	GameObjectGuiButton *m_pStartButton, *m_pAuthorsButton, *m_pExitButton;

	friend class GameController;
};

#endif // GAMESCENEMAINMENU_H
