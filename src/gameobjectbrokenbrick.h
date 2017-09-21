#ifndef GAMEOBJECTBROKENBRICK_H
#define GAMEOBJECTBROKENBRICK_H

#include "gameobject.h"

class GraphicsObject;
class PhysicsBody;

class GameObjectBrokenBrick : public GameObject
{
public:
	void breakDown();

protected:
	GameObjectBrokenBrick(GameAbstractScene *pScene);
	~GameObjectBrokenBrick();

	void update(uint32_t dt);
	void use();

private:
	struct Part {
		Transform *pTransform;
		GraphicsObject *pGraphicsObject;
		PhysicsBody *pPhysicsBody;
	};
	using PartsList = std::list<Part*>;

	PartsList m_parts;
	bool m_isWhole;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTBROKENBRICK_H
