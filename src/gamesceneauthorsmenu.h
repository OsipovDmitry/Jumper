#ifndef GAMESCENEAUTHORSMENU_H
#define GAMESCENEAUTHORSMENU_H

#include "gameabstractscene.h"

class GameObjectGuiButton;

class GameSceneAuthorsMenu : public GameAbstractScene
{
public:

protected:
	//void update(uint64_t time, uint32_t dt);
	void mouseClick(int32_t x, int32_t y);

private:
	GameSceneAuthorsMenu();
	~GameSceneAuthorsMenu();

	GameObjectGuiButton *m_pBackButton;

	friend class GameController;
};

#endif // GAMESCENEAUTHORSMENU_H
