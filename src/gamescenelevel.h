#ifndef GAMESCENELEVEL_H
#define GAMESCENELEVEL_H

#include "gameabstractscene.h"

class GameObjectPlayer;
class GameObjectGuiButton;

class GameSceneLevel : public GameAbstractScene
{
public:

protected:
	void update(uint64_t time, uint32_t dt);
	void mouseClick(int32_t x, int32_t y);

private:
	GameSceneLevel();
	~GameSceneLevel();

	GameObjectPlayer *m_pPlayer;
	GameObjectGuiButton *m_pButtonStart, *m_pButtonExit;

	friend class GameController;
};

#endif // GAMESCENELEVEL_H
