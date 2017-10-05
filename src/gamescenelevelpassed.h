#ifndef GAMESCENELEVELPASSED_H
#define GAMESCENELEVELPASSED_H

#include "gameabstractscene.h"
#include "types.h"

class GameObjectGuiButton;

class GameSceneLevelPassed : public GameAbstractScene
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
	GameSceneLevelPassed();

	GameObjectGuiButton *m_pButtonMenu, *m_pButtonRestart, *m_pButtonNext;
	GameLevelId m_passedLevelId;

	friend class GameController;
};

#endif // GAMESCENELEVELPASSED_H
