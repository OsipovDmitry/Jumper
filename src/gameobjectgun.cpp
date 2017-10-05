#include <algorithm>

#include "mathutils.h"
#include "graphicsscene.h"
#include "graphicsobject.h"
#include "physicsscene.h"
#include "physicsbody.h"
#include "physicsgeometry.h"
#include "gameabstractscene.h"
#include "gameobjectgun.h"

const float GameObjectGun::s_gunHeight = 0.3f;
const float GameObjectGun::s_gunWidth = 2 * GameObjectGun::s_gunHeight;

bool GameObjectGun::setParam(const std::string& key, const std::string& value)
{
	if (GameObject::setParam(key, value))
		return true;

	static const std::string s_orientTag = "orient";
	static const std::string s_leftOrientValue = "left";
	static const std::string s_rightOrientValue = "right";
	static const std::string s_shotTime = "shot_time";

	if (key == s_orientTag) {
		bool isLeftOrient;
		if (value == s_leftOrientValue) isLeftOrient = true;
		else if (value == s_rightOrientValue) isLeftOrient = false;
		else return false;
		setLeftOrient(isLeftOrient);
		return true;
	} else if (key == s_shotTime) {
		setShotTime(static_cast<float>(atof(value.c_str())));
		return true;
	}

	return false;
}

void GameObjectGun::setShotTime(float value)
{
	m_shotTime = value;
}

float GameObjectGun::shotTime() const
{
	return m_shotTime;
}

void GameObjectGun::setLeftOrient(bool value)
{
	m_isLeftOrient = value;
	//TODO: если правая ориентация, то нужно как-то развернуть текстуру:)
	//Или рисовать еще одну, но отзеркаленную, или как-то прокидывать в рендерер в textureMatrix.
	//Проще, конечно, еще одну нарисовать.
}

bool GameObjectGun::isLeftOrient() const
{
	return m_isLeftOrient;
}

void GameObjectGun::setTransform(const Transform& value)
{
	m_restTransform = *m_pTransform = value;
	m_nextShotTime = 0;
}

void GameObjectGun::update(uint32_t dt)
{
	BulletsList fallenBullets;
	for (auto p: m_bullets) {
		if (p->pTransform->pos.y < GLOBAL_DOWN)
			fallenBullets.push_back(p);
	}
	for (auto p: fallenBullets)
		delBullet(p);

	m_nextShotTime += dt;

	static const float s_kickTime = 0.05f;
	static const float s_returnTime = 2.0f;
	static const float s_kickDist = s_gunWidth * 0.3f;

	*m_pTransform = m_restTransform;
	if (m_shotTime >= s_kickTime + s_returnTime) {
		float coef = 0.0f;
		if (m_nextShotTime < 1000 * s_kickTime)
			coef = 0.001f * m_nextShotTime / s_kickTime;
		else if (m_nextShotTime < 1000 * (s_kickTime+s_returnTime))
			coef = (s_kickTime+s_returnTime - m_nextShotTime*0.001f) / s_returnTime;
		m_pTransform->pos += toWorldSpace(m_pTransform, glm::vec2((m_isLeftOrient ? +1.0f : -1.0f) * coef * s_kickDist, 0.0f), true);
	}

	if (m_nextShotTime >= 1000 * m_shotTime) {
		m_nextShotTime -= 1000 * m_shotTime;
		createNewShot();
	}
}

GameObjectGun::GameObjectGun(GameAbstractScene* pScene) :
	GameObject(pScene),
	m_bullets(),
	m_restTransform(*m_pTransform),
	m_nextShotTime(0),
	m_shotTime(2.5f),
	m_isLeftOrient(true)
{
	auto pGunGraphicsObject = pScene->graphicsScene()->addObject(m_pTransform);
	pGunGraphicsObject->setLayer(LayerId_Objects);
	pGunGraphicsObject->setSize(glm::vec2(s_gunWidth, s_gunHeight));
	pGunGraphicsObject->setTexture(TextureId_Gun);
	m_graphicsObjects.push_back(pGunGraphicsObject);

	auto pPhysicsGeom = pScene->physicsScene()->addStaticBox(m_pTransform, s_gunWidth, s_gunHeight);
	m_physicsGeoms.push_back(pPhysicsGeom);
}

GameObjectGun::~GameObjectGun()
{
	while (!m_bullets.empty()) {
		delBullet(m_bullets.front());
	}
}

GameObjectGun::Bullet *GameObjectGun::createNewShot()
{
	static const auto bulletRadius = 0.06f;
	static const auto bulletVel = glm::normalize(glm::vec2(2.0f, 1.0f));
	static const auto bulletVelAbs = 4.0f;

	auto pBullet = new Bullet;

	auto gunHalfSize = 0.5f * glm::vec2(s_gunWidth, s_gunHeight);
	auto bulletStartPos = toWorldSpace(m_pTransform,
									   glm::vec2((m_isLeftOrient ? -1 : +1) * gunHalfSize.x, gunHalfSize.y) +
									   1.3f * glm::vec2((m_isLeftOrient ? -1 : +1) * bulletRadius, bulletRadius));
	pBullet->pTransform = new Transform(bulletStartPos);

	pBullet->pGraphicsObject = m_pScene->graphicsScene()->addObject(pBullet->pTransform);
	pBullet->pGraphicsObject->setLayer(LayerId_Objects);
	pBullet->pGraphicsObject->setSize(glm::vec2(2*bulletRadius, 2*bulletRadius));
	pBullet->pGraphicsObject->setTexture(TextureId_Circle);

	pBullet->pPhysicsBody = m_pScene->physicsScene()->addBody(pBullet->pTransform);
	pBullet->pPhysicsBody->setVelocity(bulletVelAbs * toWorldSpace(m_pTransform, glm::vec2((m_isLeftOrient ? -1 : +1) * bulletVel.x, bulletVel.y), true));

	pBullet->pPhysicsGeom = m_pScene->physicsScene()->addDynamicSphere(pBullet->pPhysicsBody, bulletRadius);

	m_bullets.push_back(pBullet);
	return pBullet;
}

void GameObjectGun::delBullet(Bullet* pBullet)
{
	auto it = std::find(m_bullets.begin(), m_bullets.end(), pBullet);
	assert(it != m_bullets.end());

	m_pScene->physicsScene()->delGeometry(pBullet->pPhysicsGeom);
	m_pScene->physicsScene()->delBody(pBullet->pPhysicsBody);
	m_pScene->graphicsScene()->delObject(pBullet->pGraphicsObject);
	delete pBullet->pTransform;
	delete pBullet;

	m_bullets.erase(it);
}
