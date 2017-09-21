#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <inttypes.h>

class GameAbstractScene;

class PhysicsBody;
class PhysicsGeometry;
class GraphicsObject;
class GameObjectAbstractModifier;

struct Transform;

class GameObject
{
public:
	using GraphicsObjectsList = std::list<GraphicsObject*> ;
	using PhysicsBodiesList = std::list<PhysicsBody*>;
	using PhysicsGeometriesList = std::list<PhysicsGeometry*>;
	using ObjectModifiers = std::list<GameObjectAbstractModifier*>;

	GameAbstractScene *scene() const;

	virtual const Transform& transform() const;
	virtual void setTransform(const Transform& value);

//	const GraphicsObjectsList& graphicsObjects() const;
//	const PhysicsBodiesList& physicsBodies() const;
//	const PhysicsGeometriesList& physicsGeometries() const;

	template <typename ModType, typename... Ts>
	ModType *addModifier(Ts&&... params) {
		ModType *pMod = new ModType(this, std::forward<Ts>(params)...);
		m_modifiers.push_back(static_cast<GameObjectAbstractModifier*>(pMod));
		return pMod;
	}
	void delModifier(GameObjectAbstractModifier *pModifier);

protected:
	GameAbstractScene *m_pScene;
	Transform *m_pTransform;
	GraphicsObjectsList m_graphicsObjects;
	PhysicsBodiesList m_physicsBodies;
	PhysicsGeometriesList m_physicsGeoms;

	GameObject(GameAbstractScene *pScene);
	virtual ~GameObject();

	virtual void update(uint32_t dt) { (void)dt; }
	virtual void use() {}

private:
	void updateObject(uint32_t dt);

	ObjectModifiers m_modifiers;

	friend class GameAbstractScene;
	friend class GameController;
};

#endif // GAMEOBJECT_H
