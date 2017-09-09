#ifndef PHYSICSSCENE_H
#define PHYSICSSCENE_H

#include <list>
#include <inttypes.h>

#include "glm/vec2.hpp"

struct Transform;
class PhysicsBody;
class PhysicsGeometry;

class PhysicsScene
{
public:
	typedef std::list<PhysicsBody*> BodiesList;
	typedef std::list<PhysicsGeometry*> GeometriesList;

	void setGravity(const glm::vec2& value);
	const glm::vec2& gravity() const;

	PhysicsBody *addBody(Transform *pTransform);
	void delBody(PhysicsBody *pBody);

	PhysicsGeometry *addStaticSphere(const Transform *pTransform, float radius);
	PhysicsGeometry *addDynamicSphere(PhysicsBody *pBody, float radius);

	PhysicsGeometry *addStaticBox(const Transform *pTransform, float width, float height);
	PhysicsGeometry *addDynamicBox(PhysicsBody *pBody, float width, float height);

	void delGeometry(PhysicsGeometry *pGeom);

private:
	PhysicsScene();
	~PhysicsScene();

	void update(uint32_t dt);
	void simulationStep(uint32_t dt);

	static const uint32_t s_simulationStepTime = 33;
	BodiesList m_bodies;
	GeometriesList m_geoms;
	glm::vec2 m_gravity;

	friend class PhysicsController;
};

#endif // PHYSICSSCENE_H
