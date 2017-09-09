#include "graphicscamera.h"
#include "types.h"

Transform* GraphicsCamera::transform() const
{
	return m_pTransform;
}

GraphicsCamera::GraphicsCamera() :
	m_pTransform(new Transform)
{
}

GraphicsCamera::~GraphicsCamera()
{
	delete m_pTransform;
}
