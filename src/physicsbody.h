#ifndef PHYSICSBODY_H
#define PHYSICSBODY_H

#include <inttypes.h>

#include "glm/vec2.hpp"

struct Transform;
class PhysicsScene;

class PhysicsBody
{
public:
	const PhysicsScene *scene() const;
	Transform *transform() const;

	void addForce(const glm::vec2& value);

	glm::vec2 velocity() const;
	void setVelocity(const glm::vec2& value);

private:
	PhysicsBody(const PhysicsScene *pScene, Transform *pTransform);
	~PhysicsBody();

	void update(uint32_t dt);

	const PhysicsScene *m_pScene;
	Transform *m_pTransform;

	glm::vec2 m_vel, m_forces;
	float m_mass;

	friend class PhysicsScene;
};

#endif // PHYSICSBODY_H
