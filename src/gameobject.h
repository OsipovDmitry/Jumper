#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <list>
#include <inttypes.h>

class GameAbstractScene;

#define GAME_OBJECT_META(TYPE) \
	public: \
	static Type typeOfClass() { return TYPE; }


class PhysicsBody;
class PhysicsGeometry;
class GraphicsObject;
class GameObjectAbstractModifier;

struct Transform;

class GameObject
{
public:
	enum Type {
		Type_None = -1,

		Type_Background = 0,
		Type_Brick,
		Type_BrokenBrick,
		Type_Player,
		Type_Gun,
		Type_Text,
		Type_LevelPassed,
		Type_Spike,

		Type_GuiButton
	};

	using GraphicsObjectsList = std::list<GraphicsObject*> ;
	using PhysicsBodiesList = std::list<PhysicsBody*>;
	using PhysicsGeometriesList = std::list<PhysicsGeometry*>;
	using ObjectModifiers = std::list<GameObjectAbstractModifier*>;

	GameAbstractScene *scene() const;
	Type type() const;

	virtual const Transform& transform() const;
	virtual void setTransform(const Transform& value);
	virtual bool setParam(const std::string& key, const std::string& value);

	void show(bool state = true);
	void hide();

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
	Type m_type;
	Transform *m_pTransform;
	GraphicsObjectsList m_graphicsObjects;
	PhysicsBodiesList m_physicsBodies;
	PhysicsGeometriesList m_physicsGeoms;

	GameObject(GameAbstractScene *pScene, Type type);
	virtual ~GameObject();

	virtual void update(uint32_t dt) { (void)dt; }
	virtual void use() {}

private:
	void updateObject(uint32_t dt);

	ObjectModifiers m_modifiers;

	friend class GameAbstractScene;
	friend class GameController;
};

template<typename GameObjectClass>
inline GameObjectClass *game_object_cast(GameObject *pGameObject) {
	return (pGameObject->type() == GameObjectClass::typeOfClass()) ? static_cast<GameObjectClass*>(pGameObject) : nullptr;
}

#endif // GAMEOBJECT_H
