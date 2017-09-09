#ifndef PHYSICSGEOMETRY_H
#define PHYSICSGEOMETRY_H

#include "glm/vec4.hpp"

struct Transform;
class PhysicsScene;
class PhysicsBody;

class PhysicsGeometry
{
public:
	enum Type {
		Type_Sphere,
		Type_Box
	};

	Type type() const;
	const PhysicsScene *scene() const;
	PhysicsBody *body() const;

	static bool isStatic(PhysicsGeometry *pGeom) { return pGeom->m_pBody == nullptr; }
	static bool collisionDetection(PhysicsGeometry *pGeom1, PhysicsGeometry *pGeom2, glm::vec2& n, float& depth);
	static bool sphereVsSphere(const Transform *pTransform1, float r1, const Transform *pTransform2, float r2, glm::vec2& n, float& depth);
	static bool sphereVsBox(const Transform *pTransform1, float r1, const Transform *pTransform2, float w2, float h2, glm::vec2& n, float& depth);
	static bool boxVsBox(const Transform *pTransform1, float w1, float h1, const Transform *pTransform2, float w2, float h2, glm::vec2& n, float& depth);

private:
	PhysicsGeometry(Type type, const PhysicsScene *pScene, const Transform *pTransform, const glm::vec4& params);
	PhysicsGeometry(Type type, PhysicsBody *pBody, const glm::vec4& params);
	~PhysicsGeometry();

	glm::vec4 m_params;
	const PhysicsScene *m_pScene;
	PhysicsBody *m_pBody;
	const Transform *m_pTransform;
	Type m_type;

	friend class PhysicsScene;
};

#endif // PHYSICSGEOMETRY_H
