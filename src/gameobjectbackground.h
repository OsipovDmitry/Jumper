#ifndef GAMEOBJECTBACKGROUND_H
#define GAMEOBJECTBACKGROUND_H

#include "gameobject.h"
#include "types.h"

class GraphicsObject;

class GameObjectBackground : public GameObject
{
GAME_OBJECT_META(Type_Background)
public:
	bool setParam(const std::string& key, const std::string& value) override;

	void setBackgroundId(BackgroundId id);
	BackgroundId backgrounId() const;

private:
	GameObjectBackground(GameAbstractScene *pScene, BackgroundId id);
	~GameObjectBackground();

	static BackgroundId paramToBackgroundId(const std::string& param);

	GraphicsObject *m_pGraphicsObject;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTBACKGROUND_H
