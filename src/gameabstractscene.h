#ifndef GAMEABSTRACTSCENE_H
#define GAMEABSTRACTSCENE_H

#include <list>
#include <inttypes.h>

class GraphicsScene;
class PhysicsScene;
class GameObject;
class GameObjectBackground;

class GameAbstractScene
{
public:
	GraphicsScene *graphicsScene() const;
	PhysicsScene *physicsScene() const;

protected:
	using ObjectsList = std::list<GameObject*>;

	ObjectsList m_objects;
	GameObjectBackground *m_pObjectBackground;
	GraphicsScene *m_pGraphicsScene;
	PhysicsScene *m_pPhysicsScene;

	GameAbstractScene();
	~GameAbstractScene();

	void delObject(GameObject *pObject);

	template <typename ObjectType, typename... Ts>
	ObjectType *createGameObject(Ts&&... params) {
		ObjectType *pObject = new ObjectType(this, std::forward<Ts>(params)...);
		m_objects.push_back(static_cast<GameObject*>(pObject));
		return pObject;
	}

	virtual void update(uint64_t, uint32_t) {}
	virtual void mouseClick(int32_t x, int32_t y);

	ObjectsList selectObjects(int32_t x, int32_t y);

private:
	void updateScene(uint64_t time, uint32_t dt);

	friend class GameController;
};

#endif // GAMEABSTRACTSCENE_H
