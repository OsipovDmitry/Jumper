#ifndef GAMEOBJECTMODIFIERTRAIN_H
#define GAMEOBJECTMODIFIERTRAIN_H

#include <vector>

#include "gameobjectabstractmodifier.h"
#include "types.h"

class GameObjectModifierTrain : public GameObjectAbstractModifier
{
public:
	struct KeyFrame {
		Transform transform;
		float dtime;

		KeyFrame(const Transform& tr, const float dt) : transform(tr), dtime(dt) {}
	};
	using KeyFramesList = std::vector<KeyFrame>;

	KeyFramesList& keyFramesList();
	const KeyFramesList& keyFramesList() const;

	void setLoop(bool value);
	bool isLoop() const;

protected:
	GameObjectModifierTrain(GameObject *pObject);
	~GameObjectModifierTrain();

	void update(uint32_t dt);

private:
	KeyFramesList m_keyFrames;
	bool m_isLoop;
	float m_currTime;

	friend class GameObject;
};

#endif // GAMEOBJECTMODIFIERTRAIN_H
