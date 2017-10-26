#include <algorithm>

#include "glm/geometric.hpp"
#include "types.h"
#include "physicsscene.h"
#include "physicsbody.h"
#include "physicsgeometry.h"

void PhysicsScene::setGravity(const glm::vec2& value)
{
	m_gravity = value;
}

const glm::vec2& PhysicsScene::gravity() const
{
	return m_gravity;
}

PhysicsBody *PhysicsScene::addBody(Transform* pTransform)
{
	PhysicsBody *pBody = new PhysicsBody(this, pTransform);
	m_bodies.push_back(pBody);
	return pBody;
}

void PhysicsScene::delBody(PhysicsBody* pBody)
{
	assert(pBody->scene() == this);
	auto it = std::find(m_bodies.begin(), m_bodies.end(), pBody);
	assert(it != m_bodies.end());

	m_bodies.erase(it);
	delete pBody;
}

PhysicsGeometry *PhysicsScene::addStaticSphere(const Transform* pTransform, float radius)
{
	PhysicsGeometry *pGeom = new PhysicsGeometry(PhysicsGeometry::Type_Sphere, this, pTransform, glm::vec4(radius, 0.0f, 0.0f, 0.0f));
	m_geoms.push_back(pGeom);
	return pGeom;
}

PhysicsGeometry *PhysicsScene::addDynamicSphere(PhysicsBody* pBody, float radius)
{
	assert(pBody->scene() == this);
	PhysicsGeometry *pGeom = new PhysicsGeometry(PhysicsGeometry::Type_Sphere, pBody, glm::vec4(radius, 0.0f, 0.0f, 0.0f));
	m_geoms.push_back(pGeom);
	return pGeom;
}

PhysicsGeometry *PhysicsScene::addStaticBox(const Transform* pTransform, float width, float height)
{
	PhysicsGeometry *pGeom = new PhysicsGeometry(PhysicsGeometry::Type_Box, this, pTransform, glm::vec4(width, height, 0.0f, 0.0f));
	m_geoms.push_back(pGeom);
	return pGeom;
}

PhysicsGeometry *PhysicsScene::addDynamicBox(PhysicsBody* pBody, float width, float height)
{
	assert(pBody->scene() == this);
	PhysicsGeometry *pGeom = new PhysicsGeometry(PhysicsGeometry::Type_Box, pBody, glm::vec4(width, height, 0.0f, 0.0f));
	m_geoms.push_back(pGeom);
	return pGeom;
}

void PhysicsScene::delGeometry(PhysicsGeometry* pGeom)
{
	assert(pGeom->scene() == this);
	auto it = std::find(m_geoms.begin(), m_geoms.end(), pGeom);
	assert(it != m_geoms.end());

	m_geoms.erase(it);
	delete pGeom;
}

void PhysicsScene::setCollisionDetectionCallback(CollisionDetectionCallback func, void* pData)
{
	m_cdCallback = func;
	m_cdData = pData;
}

PhysicsScene::PhysicsScene() :
	m_bodies(),
	m_geoms(),
	m_gravity(0.0f, 0.0f),
	m_cdCallback(nullptr),
	m_cdData(nullptr)
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto it = m_bodies.begin(); it != m_bodies.end(); ++it)
		delete (*it);
	m_bodies.clear();

	for (auto it = m_geoms.begin(); it != m_geoms.end(); ++it)
		delete (*it);
	m_geoms.clear();
}

void PhysicsScene::update(uint32_t dt)
{
	while (dt > 0) {
		uint32_t stepTime = (dt >= s_simulationStepTime) ? s_simulationStepTime : dt;
		simulationStep(stepTime);
		dt -= stepTime;
	}
}

void PhysicsScene::simulationStep(uint32_t dt)
{
	for (auto pBody: m_bodies) {
		pBody->addForce(m_gravity);
		pBody->update(dt);
	}

	static const float dampVel = 0.8f;

	glm::vec2 normal;
	float depth;
	for (auto it1 = m_geoms.begin(); it1 != m_geoms.end(); ++it1)
		for (auto it2 = ++(GeometriesList::iterator(it1)); it2 != m_geoms.end(); ++it2) {
			if ((*it1)->body() == (*it2)->body()) // в том числе nullptr == nullptr, то есть оба статичны
				continue;

			if (!PhysicsGeometry::collisionDetection(*it1, *it2, normal, depth))
				continue;

			if (!PhysicsGeometry::isStatic(*it1)) {
				(*it1)->m_pBody->m_pTransform->pos -= normal * depth;
				(*it1)->m_pBody->m_vel = glm::reflect((*it1)->m_pBody->m_vel, normal) * dampVel;
			}
			if (!PhysicsGeometry::isStatic(*it2)) {
				(*it2)->m_pBody->m_pTransform->pos += normal * depth;
				(*it2)->m_pBody->m_vel = glm::reflect((*it2)->m_pBody->m_vel, -normal) * dampVel;
			}

			if (m_cdCallback)
				m_cdCallback(m_cdData, *it1, *it2);
		}
}
