#ifndef GAMESCENEGAMEOVER_H
#define GAMESCENEGAMEOVER_H

#include "gameabstractscene.h"
#include "types.h"

class GameObjectGuiButton;

class GameSceneGameOver : public GameAbstractScene
{
public:
	class ActivateData : public GameAbstractScene::AbstractActivateData {
	public:
		ActivateData(GameLevelId id) : levelId(id) {}

		GameLevelId levelId;
	};

protected:
	void mouseClick(int32_t x, int32_t y);
	void activate(AbstractActivateData *pData);

private:
	GameSceneGameOver();
	~GameSceneGameOver();

	GameObjectGuiButton *m_pButtonMenu, *m_pButtonRestart;
	GameLevelId	m_overLevelId;

	friend class GameController;
};

#endif // GAMESCENEGAMEOVER_H
