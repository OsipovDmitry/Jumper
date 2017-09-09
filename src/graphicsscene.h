#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <list>

#include "types.h"

class GraphicsObject;
class GraphicsCamera;

class GraphicsScene
{
public:
	typedef std::list<GraphicsObject*> ObjectsList;

	GraphicsObject *addObject(const Transform *pTransform);
	void delObject(GraphicsObject *pObject);

	GraphicsCamera* camera() const;

private:
	GraphicsScene();
	~GraphicsScene();

	ObjectsList m_objects;

	GraphicsCamera *m_pCamera;

	void show();
	void hide();

	friend class GraphicsController;
};

#endif // GRAPHICSSCENE_H
