#include <cassert>

#include "glm/geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "types.h"
#include "physicsgeometry.h"
#include "physicsbody.h"

PhysicsGeometry::Type PhysicsGeometry::type() const
{
	return m_type;
}

const PhysicsScene* PhysicsGeometry::scene() const
{
	return m_pScene;
}

PhysicsBody*PhysicsGeometry::body() const
{
	return m_pBody;
}

void PhysicsGeometry::setData(void *pData)
{
	m_pData = pData;
}

void *PhysicsGeometry::data() const
{
	return m_pData;
}

bool PhysicsGeometry::collisionDetection(PhysicsGeometry* pGeom1, PhysicsGeometry* pGeom2, glm::vec2& n, float& depth)
{
	const Transform *pTr1 = isStatic(pGeom1) ? pGeom1->m_pTransform : pGeom1->m_pBody->transform();
	const Transform *pTr2 = isStatic(pGeom2) ? pGeom2->m_pTransform : pGeom2->m_pBody->transform();

	Type t1 = pGeom1->m_type;
	Type t2 = pGeom2->m_type;

	if (t1 == Type_Sphere) {
		if (t2 == Type_Sphere)
			return sphereVsSphere(pTr1, pGeom1->m_params.x, pTr2, pGeom2->m_params.x, n, depth);
		else if (t2 == Type_Box)
			return sphereVsBox(pTr1, pGeom1->m_params.x, pTr2, pGeom2->m_params.x, pGeom2->m_params.y, n, depth);
		else
			return false;
	}
	else if (t1 == Type_Box) {
		if (t2 == Type_Sphere) {
			bool res = sphereVsBox(pTr2, pGeom2->m_params.x, pTr1, pGeom1->m_params.x, pGeom1->m_params.y, n, depth);
			n = -n;
			return res;
		}
		else if (t2 == Type_Box)
			return boxVsBox(pTr1, pGeom1->m_params.x, pGeom1->m_params.y, pTr2, pGeom2->m_params.x, pGeom2->m_params.y, n, depth);
		else
			return false;
	}
	else
		return false;
}

bool PhysicsGeometry::sphereVsSphere(const Transform* pTransform1, float r1, const Transform* pTransform2, float r2, glm::vec2& n, float& depth)
{
	n = pTransform2->pos - pTransform1->pos;
	float dist = glm::length(n);
	n /= dist;
	depth = r1 + r2 - dist;
	return depth > 0.0f;
}

bool PhysicsGeometry::sphereVsBox(const Transform* pTransform1, float r1, const Transform* pTransform2, float w2, float h2, glm::vec2& n, float& depth)
{
	glm::vec2 sphereNewPos = glm::vec2(
		glm::rotate(glm::mat4x4(), -pTransform2->angle, glm::vec3(0.0f,0.0f,1.0f)) *
		glm::translate(glm::mat4x4(), glm::vec3(-pTransform2->pos, 0.0f)) *
		glm::vec4(pTransform1->pos, 0.0f, 1.0f)
	);

	const glm::vec2 boxHalfSize(w2 * 0.5f, h2 * 0.5f);
	n = glm::vec2(0.0f,0.0f);
	depth = 0.0f;
	for (int i = 0; i < 2; ++i) {
		float d = 0.0f;
		if (sphereNewPos[i] > boxHalfSize[i]) {
			d = sphereNewPos[i] - boxHalfSize[i];
			n[i] = -1.0f;
		}
		else if (sphereNewPos[i] < -boxHalfSize[i]) {
			d = -boxHalfSize[i] - sphereNewPos[i];
			n[i] = 1.0f;
		}
		depth += d*d;
	}

	const float nLen = glm::length(n);
	if (nLen > 0.0) {
		n = n / nLen;
		n = glm::vec2(
			glm::rotate(glm::mat4x4(), pTransform2->angle, glm::vec3(0.0f,0.0f,1.0f)) *
			glm::vec4(n, 0.0f, 1.0f)
		);
	}
	depth = glm::max(0.0f, r1 - glm::sqrt(depth));
	return depth > 0.0f;
}

bool PhysicsGeometry::boxVsBox(const Transform* pTransform1, float w1, float h1, const Transform* pTransform2, float w2, float h2, glm::vec2& n, float& depth)
{
	(void)pTransform1;
	(void)w1;
	(void)h1;
	(void)pTransform2;
	(void)w2;
	(void)h2;
	(void)n;
	(void)depth;
	return false;
}

PhysicsGeometry::PhysicsGeometry(Type type, const PhysicsScene* pScene, const Transform *pTransform, const glm::vec4& params) :
	m_params(params),
	m_pScene(pScene),
	m_pBody(nullptr),
	m_pTransform(pTransform),
	m_type(type),
	m_pData(nullptr)
{

}

PhysicsGeometry::PhysicsGeometry(Type type, PhysicsBody *pBody, const glm::vec4& params) :
	m_params(params),
	m_pScene(pBody->scene()),
	m_pBody(pBody),
	m_pTransform(nullptr),
	m_type(type),
	m_pData(nullptr)
{
	//assert(pBody == nullptr);
}

PhysicsGeometry::~PhysicsGeometry()
{

}
