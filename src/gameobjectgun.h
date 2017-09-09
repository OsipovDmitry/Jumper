#ifndef GAMEOBJECTGUN_H
#define GAMEOBJECTGUN_H

#include <inttypes.h>

#include "gameobject.h"

class GameObjectGun : public GameObject
{
public:
	void setShotTime(uint32_t value);
	uint32_t shotTime() const;

	void setLeftOrient(bool value);
	bool isLeftOrient() const;

protected:
	void update(uint32_t dt);

private:
	struct Bullet {
		Transform *pTransform;
		GraphicsObject *pGraphicsObject;
		PhysicsBody *pPhysicsBody;
		PhysicsGeometry *pPhysicsGeom;
	};
	using BullletsList = std::list<Bullet*>;

	GameObjectGun(GameAbstractScene *pScene);
	~GameObjectGun();

	Bullet *createNewShot();
	void delBullet(Bullet *pBullet);

	BullletsList m_bullets;
	int32_t m_nextShotTime;
	uint32_t m_shotTime;

	bool m_isLeftOrient;

	static const float s_gunHeight;
	static const float s_gunWidth;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTGUN_H
