#ifndef GAMEABSTRACTSCENE_H
#define GAMEABSTRACTSCENE_H

#include <list>
#include <inttypes.h>

class GraphicsScene;
class PhysicsScene;
class PhysicsGeometry;
class GameObject;
class GameObjectBackground;

class GameAbstractScene
{
public:
	class AbstractActivateData {
	public:
		virtual ~AbstractActivateData() = default;
	};

	GraphicsScene *graphicsScene() const;
	PhysicsScene *physicsScene() const;

protected:
	using ObjectsList = std::list<GameObject*>;

	ObjectsList m_objects;
	GameObjectBackground *m_pBackgroundObject;
	GraphicsScene *m_pGraphicsScene;
	PhysicsScene *m_pPhysicsScene;

	GameAbstractScene();
	virtual ~GameAbstractScene();

	template <typename ObjectType, typename... Ts>
	ObjectType *createGameObject(Ts&&... params) {
		ObjectType *pObject = new ObjectType(this, std::forward<Ts>(params)...);
		m_objects.push_back(static_cast<GameObject*>(pObject));
		return pObject;
	}
	void delGameObject(GameObject *pObject);

	virtual void update(uint32_t) {}
	virtual void mouseClick(int32_t, int32_t) {}
	virtual void activate(AbstractActivateData*) {}

	ObjectsList selectObjects(int32_t x, int32_t y);

private:
	void updateScene(uint32_t dt);
	void collisionDetection(PhysicsGeometry *p1, PhysicsGeometry *p2);

	static void collisionDetection(void *pSceneData, PhysicsGeometry *p1, PhysicsGeometry *p2);

	friend class GameController;
};

#endif // GAMEABSTRACTSCENE_H
