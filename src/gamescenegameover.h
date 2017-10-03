#ifndef GAMESCENEGAMEOVER_H
#define GAMESCENEGAMEOVER_H

#include "gameabstractscene.h"

class GameObjectGuiButton;

class GameSceneGameOver : public GameAbstractScene
{
public:
protected:
	void mouseClick(int32_t x, int32_t y);

private:
	GameSceneGameOver();
	~GameSceneGameOver();

	GameObjectGuiButton *m_pButtonMenu, *m_pButtonRestart;

	friend class GameController;
};

#endif // GAMESCENEGAMEOVER_H
