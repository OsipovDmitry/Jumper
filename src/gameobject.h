#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <inttypes.h>

class GameAbstractScene;

class PhysicsBody;
class PhysicsGeometry;
class GraphicsObject;

struct Transform;

class GameObject
{
public:
	typedef std::list<GraphicsObject*> GraphicsObjectsList;
	typedef std::list<PhysicsBody*> PhysicsBodiesList;
	typedef std::list<PhysicsGeometry*> PhysicsGeometriesList;

	GameAbstractScene *scene() const;
	Transform *transform() const;
	const GraphicsObjectsList& graphicsObjects() const;
	const PhysicsBodiesList& physicsBodies() const;
	const PhysicsGeometriesList& physicsGeometries() const;

protected:
	GameAbstractScene *m_pScene;
	Transform *m_pTransform;
	GraphicsObjectsList m_graphicsObjects;
	PhysicsBodiesList m_physicsBodies;
	PhysicsGeometriesList m_physicsGeoms;

	GameObject(GameAbstractScene *pScene);
	virtual ~GameObject();

	virtual void update(uint32_t dt) {}

	friend class GameAbstractScene;
};

#endif // GAMEOBJECT_H
