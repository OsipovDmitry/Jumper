#include "physicsbody.h"
#include "types.h"

const PhysicsScene *PhysicsBody::scene() const
{
	return m_pScene;
}

Transform*PhysicsBody::transform() const
{
	return m_pTransform;
}

void PhysicsBody::addForce(const glm::vec2& value)
{
	m_forces += value;
}

glm::vec2 PhysicsBody::velocity() const
{
	return m_vel;
}

void PhysicsBody::setVelocity(const glm::vec2& value)
{
	m_vel = value;
}

PhysicsBody::PhysicsBody(const PhysicsScene* pScene, Transform* pTransform) :
	m_pScene(pScene),
	m_pTransform(pTransform),
	m_vel(),
	m_mass(1.0f)
{

}

PhysicsBody::~PhysicsBody()
{

}

void PhysicsBody::update(uint32_t dt)
{
	float deltaTime = 0.001f * dt;
	glm::vec2 acc = m_forces / m_mass;
	m_vel += acc * deltaTime;
	m_pTransform->pos += m_vel * deltaTime;

	m_forces = glm::vec2(0.0f, 0.0f);
}
