#ifndef GAMEOBJECTROTATEMODIFIER_H
#define GAMEOBJECTROTATEMODIFIER_H

#include "gameobjectabstractmodifier.h"

class GameObjectModifierRotate : public GameObjectAbstractModifier
{
public:
	void setRotateVelocity(const float value);
	float rotateVelocity() const;

protected:
	GameObjectModifierRotate(GameObject *pObject, float rotateVel);
	~GameObjectModifierRotate();

	void update(uint32_t dt);

private:
	float m_rotateVel;

	friend class GameObject;
};

#endif // GAMEOBJECTROTATEMODIFIER_H
