#ifndef PHYSICSCONTROLLER_H
#define PHYSICSCONTROLLER_H

#include <list>

#include "abstractcontroller.h"

class PhysicsScene;

class PhysicsController : public AbstractController
{
public:
	static ControllerType controllerType() { return ControllerType_Physics; }

	PhysicsScene *addScene();
	void delScene(PhysicsScene *pScene);
	PhysicsScene *currentScene();
	void setCurrentScene(PhysicsScene *pScene);

protected:
	virtual bool process(AbstractControllerMessage *pMessage);

private:
	using ScenesList = std::list<PhysicsScene*>;

	PhysicsController();
	~PhysicsController();

	void update(uint32_t dt);
	ScenesList m_scenes;
	PhysicsScene *m_pCurrentScene;

	friend class Core;
};

#endif // PHYSICSCONTROLLER_H
