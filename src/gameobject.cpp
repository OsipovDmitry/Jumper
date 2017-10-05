#include <algorithm>

#include "graphicsobject.h"
#include "gameobject.h"
#include "gameobjectabstractmodifier.h"
#include "types.h"
#include "mathutils.h"

GameAbstractScene*GameObject::scene() const
{
	return m_pScene;
}

//Transform *GameObject::transform() const
//{
//	return m_pTransform;
//}

//const GameObject::GraphicsObjectsList& GameObject::graphicsObjects() const
//{
//	return m_graphicsObjects;
//}

//const GameObject::PhysicsBodiesList& GameObject::physicsBodies() const
//{
//	return m_physicsBodies;
//}

//const GameObject::PhysicsGeometriesList& GameObject::physicsGeometries() const
//{
//	return m_physicsGeoms;
//}

void GameObject::delModifier(GameObjectAbstractModifier* pModifier)
{
	assert(pModifier->m_pGameObject == this);
	auto it = std::find(m_modifiers.begin(), m_modifiers.end(), pModifier);
	assert(it != m_modifiers.end());
	m_modifiers.erase(it);
	delete pModifier;
}

const Transform &GameObject::transform() const
{
	return *m_pTransform;
}

void GameObject::setTransform(const Transform& value)
{
	*m_pTransform = value;
}

GameObject::GameObject(GameAbstractScene *pScene) :
	m_pScene(pScene),
	m_pTransform(new Transform()),
	m_graphicsObjects(),
	m_physicsBodies(),
	m_physicsGeoms(),
	m_modifiers()
{

}

GameObject::~GameObject()
{
	while (!m_modifiers.empty())
		delModifier(m_modifiers.front());

	delete m_pTransform;
}
#include <iostream>
bool GameObject::setParam(const std::string& key, const std::string& value)
{
    std::cout << key << "=" << value << std::endl;

	static const std::string s_type = "type";
	static const std::string s_posXTag = "x";
	static const std::string s_posYTag = "y";
	static const std::string s_angleTag = "angle";

	if (key == s_type)
		return true;
	if (key == s_posXTag) {
		Transform t = transform();
        t.pos.x = static_cast<float>(stof(value.c_str()));
		setTransform(t);
		return true;
	} else if (key == s_posYTag) {
		Transform t = transform();
        t.pos.y = static_cast<float>(stof(value.c_str()));
		setTransform(t);
		return true;
	} else if (key == s_angleTag) {
		Transform t = transform();
        t.angle = static_cast<float>(stof(value.c_str()));
		setTransform(t);
		return true;
	}

	return false;
}

void GameObject::show(bool state)
{
	for (auto p: m_graphicsObjects)
		p->setVisible(state);
}

void GameObject::hide()
{
	show(false);
}

void GameObject::updateObject(uint32_t dt)
{
	for (auto p: m_modifiers)
		p->update(dt);

	update(dt);
}
