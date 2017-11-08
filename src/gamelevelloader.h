#ifndef GAMELEVELLOADER_H
#define GAMELEVELLOADER_H

#include <string>

#include "types.h"

class GameSceneLevel;

class GameLevelLoader
{
public:
	GameLevelLoader(GameSceneLevel *pTargetLevel);

	bool load(GameLevelId levelId);
	void unload();

private:
	static std::string levelIdToFilename(GameLevelId levelId);

	GameSceneLevel *m_pTargetLevel;

};

#endif // GAMELEVELLOADER_H
