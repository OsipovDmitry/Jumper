#ifndef GAMEOBJECTMODIFIEROFFSET_H
#define GAMEOBJECTMODIFIEROFFSET_H

#include "glm/vec2.hpp"
#include "gameobjectabstractmodifier.h"

class GameObjectModifierOffset : public GameObjectAbstractModifier
{
public:
	virtual bool setParam(const std::string& key, const std::string& value) override;

	glm::vec2 offset() const;
	void setOffset(const glm::vec2& value);

	float velocity() const;
	void setVelocity(const float value);

protected:
	GameObjectModifierOffset(GameObject *pObject);

	void update(uint32_t dt);

private:
	glm::vec2 m_offsetNorm;
	float m_offsetAbs, m_offsetVel, m_offsetCur;
	int32_t m_sign;

	friend class GameObject;
};

#endif // GAMEOBJECTMODIFIEROFFSET_H
