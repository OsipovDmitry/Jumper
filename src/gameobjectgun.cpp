#include <algorithm>

#include "graphicsscene.h"
#include "graphicsobject.h"
#include "physicsscene.h"
#include "physicsbody.h"
#include "physicsgeometry.h"
#include "gameabstractscene.h"
#include "gameobjectgun.h"

const float GameObjectGun::s_gunHeight = 0.3f;
const float GameObjectGun::s_gunWidth = 2 * GameObjectGun::s_gunHeight;

void GameObjectGun::setShotTime(uint32_t value)
{
	m_shotTime = value;
}

uint32_t GameObjectGun::shotTime() const
{
	return m_shotTime;
}

void GameObjectGun::setLeftOrient(bool value)
{
	m_isLeftOrient = value;
}

bool GameObjectGun::isLeftOrient() const
{
	return m_isLeftOrient;
}

void GameObjectGun::update(uint32_t dt)
{
	m_nextShotTime -= dt;
	if (m_nextShotTime <= 0) {

		BullletsList fallenBullets;
		for (auto p: m_bullets) {
			if (p->pTransform->pos.y < -500.0f)
				fallenBullets.push_back(p);
		}
		for (auto p: fallenBullets)
			delBullet(p);

		m_nextShotTime = m_shotTime;
		createNewShot();
	}
}

GameObjectGun::GameObjectGun(GameAbstractScene* pScene) :
	GameObject(pScene),
	m_bullets(),
	m_nextShotTime(0),
	m_shotTime(2500),
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
	auto bulletStartPos = m_pTransform->pos +
						  glm::vec2((m_isLeftOrient ? -1 : +1) * gunHalfSize.x, gunHalfSize.y) +
						  1.0f * glm::vec2((m_isLeftOrient ? -1 : +1) * bulletRadius, bulletRadius);
	pBullet->pTransform = new Transform(bulletStartPos);

	pBullet->pGraphicsObject = m_pScene->graphicsScene()->addObject(pBullet->pTransform);
	pBullet->pGraphicsObject->setLayer(LayerId_Objects);
	pBullet->pGraphicsObject->setSize(glm::vec2(2*bulletRadius, 2*bulletRadius));
	pBullet->pGraphicsObject->setTexture(TextureId_Circle);

	pBullet->pPhysicsBody = m_pScene->physicsScene()->addBody(pBullet->pTransform);
	pBullet->pPhysicsBody->setVelocity(bulletVelAbs * glm::vec2((m_isLeftOrient ? -1 : +1) * bulletVel.x, bulletVel.y));

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
