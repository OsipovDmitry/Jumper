#ifndef GAMEOBJECTGUN_H
#define GAMEOBJECTGUN_H

#include <inttypes.h>

#include "gameobject.h"

class GameObjectGun : public GameObject
{
GAME_OBJECT_META(Type_Gun)
public:
	bool setParam(const std::string& key, const std::string& value) override;

	void setShotTime(float value);
	float shotTime() const;

	void setLeftOrient(bool value);
	bool isLeftOrient() const;

	void setTransform(const Transform& value);

protected:
	void update(uint32_t dt);

private:
	struct Bullet {
		Transform *pTransform;
		GraphicsObject *pGraphicsObject;
		PhysicsBody *pPhysicsBody;
		PhysicsGeometry *pPhysicsGeom;
	};
	using BulletsList = std::list<Bullet*>;

	GameObjectGun(GameAbstractScene *pScene);
	~GameObjectGun();

	Bullet *createNewShot();
	void delBullet(Bullet *pBullet);

	BulletsList m_bullets;
	Transform m_restTransform;
	int32_t m_nextShotTime;
	float m_shotTime;

	bool m_isLeftOrient;

	static const float s_gunHeight;
	static const float s_gunWidth;

	friend class GameAbstractScene;
};

#endif // GAMEOBJECTGUN_H
