#ifndef GAMEOBJECTTEXT_H
#define GAMEOBJECTTEXT_H

#include "gameobject.h"

class GameObjectText : public GameObject
{
public:
	void setTransform(const Transform& value);

protected:
private:
    GameObjectText(GameAbstractScene *pScene, const std::string& str, const float textSize = 0.2f);
	~GameObjectText();

	std::list<Transform*> m_symbolTransforms;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTTEXT_H
