#ifndef GAMESCENESELECTLEVELMENU_H
#define GAMESCENESELECTLEVELMENU_H

#include "gameabstractscene.h"
#include "types.h"

class GameObjectGuiButton;

class GameSceneSelectLevel : public GameAbstractScene
{
public:

protected:
	void mouseClick(int32_t x, int32_t y);
	void activate(AbstractActivateData*);

private:
	GameSceneSelectLevel();
	~GameSceneSelectLevel();

	GameObjectGuiButton *m_pLevelButton[GameLevelId_Count], *m_pBackButton;

	friend class GameController;
};

#endif // GAMESCENESELECTLEVELMENU_H
