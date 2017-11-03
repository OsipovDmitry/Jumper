#ifndef GAMESCENELEVEL_H
#define GAMESCENELEVEL_H

#include "gameabstractscene.h"
#include "types.h"

class GameObjectPlayer;
class GameObjectGuiButton;

class GameSceneLevel : public GameAbstractScene
{
public:
	bool load(GameLevelId levelId);
	void unload();

	GameLevelId currentLevel() const;

	static GameLevelId maxOpenedLevel();
	static void setMaxOpenedLevel(GameLevelId levelId);

protected:
	void update(uint32_t dt);
	void mouseClick(int32_t x, int32_t y);
	void activate(AbstractActivateData*);

private:
	GameSceneLevel();
	~GameSceneLevel();

	static std::string levelIdToFilename(GameLevelId levelId);

	GameObjectPlayer *m_pPlayer;
	GameObjectGuiButton *m_pPauseButton;
	ObjectsList m_gameObjects;
	GameLevelId m_currentLevelId;

	friend class GameController;
};

#endif // GAMESCENELEVEL_H
