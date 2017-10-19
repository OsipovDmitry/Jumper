#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include <list>

#include "abstractcontroller.h"

class GraphicsScene;

class GraphicsController : public AbstractController
{
public:
	using ScenesList = std::list<GraphicsScene*>;

	static ControllerType controllerType() { return ControllerType_Graphics; }

	GraphicsScene *addScene();
	void delScene(GraphicsScene *pScene);
	GraphicsScene *currentScene();
	void setCurrentScene(GraphicsScene *pScene);

protected:
	virtual bool process(AbstractControllerMessage *pMessage);

private:
	GraphicsController();
	~GraphicsController();
	void update(uint32_t dt);

	ScenesList m_scenes;
	GraphicsScene *m_pCurrentScene;

	friend class Core;
};

#endif // GRAPHICSCONTROLLER_H
