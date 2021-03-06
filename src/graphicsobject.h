#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include "renderer.h"

struct Transform;
class GraphicsScene;

class GraphicsObject
{
public:
	GraphicsScene *scene() const;
	const Transform *transform() const;

	void setSize(const glm::vec2& value);
	glm::vec2 size() const;

	void setTexture(TextureId texId);
	TextureId texture() const;

	void setLayer(LayerId value);
	LayerId layer() const;

	void setColor(const Color4ub& value);
	Color4ub color() const;

	void setVisible(bool state);
	bool isVisible() const;

private:
	GraphicsObject(GraphicsScene *pScene, const Transform *pTransform);
	~GraphicsObject();

	GraphicsScene *m_pScene;
	Renderer::Sprite *m_pSprite;

	friend class GraphicsScene;
};

#endif // GRAPHICSOBJECT_H
