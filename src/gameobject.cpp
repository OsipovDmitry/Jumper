#include "gameobject.h"
#include "types.h"

GameAbstractScene*GameObject::scene() const
{
	return m_pScene;
}

Transform *GameObject::transform() const
{
	return m_pTransform;
}

const GameObject::GraphicsObjectsList& GameObject::graphicsObjects() const
{
	return m_graphicsObjects;
}

const GameObject::PhysicsBodiesList& GameObject::physicsBodies() const
{
	return m_physicsBodies;
}

const GameObject::PhysicsGeometriesList& GameObject::physicsGeometries() const
{
	return m_physicsGeoms;
}

GameObject::GameObject(GameAbstractScene *pScene) :
	m_pScene(pScene),
	m_pTransform(new Transform()),
	m_graphicsObjects(),
	m_physicsBodies(),
	m_physicsGeoms()
{

}

GameObject::~GameObject()
{
	delete m_pTransform;
}
