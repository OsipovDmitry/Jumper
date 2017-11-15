#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"

struct RendererPrivate;
class Renderer
{
public:
	struct Sprite {
		const Transform *pTransform;
		glm::vec2 size;
		TextureId textureId;
		LayerId layerId;
		Color4ub color;
		bool visible;
	};

	Sprite *createSprite(const Transform *pTransform);
	void drawSprite(Sprite *pSprite);
	void eraseSprite(Sprite *pSprite);
	void destroySprite(Sprite *pSprite);

	void setCameraTransform(const Transform *pTransform);

    glm::vec2 windowToClipSpace(const glm::ivec2& windowCoords) const;
    glm::vec2 windowToWorldSpace(const glm::ivec2& windowCoords, LayerId layerId) const;

	const glm::ivec2& texturePosInfo(TextureId textureId) const;
	const glm::ivec2& textureSizeInfo(TextureId textureId) const;

private:
	Renderer();
	~Renderer();

	void resize(int w, int h);
	void render() const;

	RendererPrivate *m;

	friend class RenderWidget;
};

#endif // RENDERER_H
