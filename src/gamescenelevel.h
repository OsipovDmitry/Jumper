#ifndef GAMESCENELEVEL_H
#define GAMESCENELEVEL_H

#include <string>

#include "gameabstractscene.h"
#include "types.h"

class GameObjectPlayer;

class GameSceneLevel : public GameAbstractScene
{
public:
	bool load(GameLevelId levelId);
	void unload();

	GameLevelId currentLevel() const;

	static GameLevelId maxOpenedLevel();
	static void setMaxOpenedLevel(GameLevelId levelId);

protected:
	void update(uint64_t time, uint32_t dt);
	void mouseClick(int32_t x, int32_t y);
	void activate(AbstractActivateData*);

private:
	GameSceneLevel();
	~GameSceneLevel();

	static std::string levelIdToFilename(GameLevelId levelId);

	GameObjectPlayer *m_pPlayer;
	ObjectsList m_gameObjects;
	GameLevelId m_currentLevelId;

	friend class GameController;
};

#endif // GAMESCENELEVEL_H
