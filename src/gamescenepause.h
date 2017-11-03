#ifndef GAMESCENEPAUSE_H
#define GAMESCENEPAUSE_H

#include "gameabstractscene.h"
#include "types.h"

class GameObjectGuiButton;

class GameScenePause : public GameAbstractScene
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
	GameScenePause();

	GameObjectGuiButton *m_pResumeButton, *m_pRestartButton, *m_pToMenuButton;
	GameLevelId	m_levelId;

	friend class GameController;
};

#endif // GAMESCENEPAUSE_H
