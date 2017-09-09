#ifndef GAMEOBJECTBACKGROUND_H
#define GAMEOBJECTBACKGROUND_H

#include "gameobject.h"
#include "types.h"

class GraphicsObject;

class GameObjectBackground : public GameObject
{
public:
	void setBackgroundId(BackgroundId id);
	BackgroundId backgrounId() const;

protected:
private:
	GameObjectBackground(GameAbstractScene *pScene);
	~GameObjectBackground();

	GraphicsObject *m_pGraphicsObject;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTBACKGROUND_H
