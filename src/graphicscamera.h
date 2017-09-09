#ifndef GRAPHICSCAMERA_H
#define GRAPHICSCAMERA_H

#include "glm/vec2.hpp"

struct Transform;

class GraphicsCamera
{
public:
	Transform *transform() const;

private:
	Transform *m_pTransform;

	GraphicsCamera();
	~GraphicsCamera();

	friend class GraphicsScene;
};

#endif // GRAPHICSCAMERA_H
