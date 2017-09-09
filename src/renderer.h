#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include <vector>
#include <string>

#include <GLES2/gl2.h>

#include "types.h"
#include "glm/mat4x4.hpp"

class Renderer
{
public:
	struct Sprite {
		const Transform *pTransform;
		glm::vec2 size;
		TextureId textureId;
		LayerId layerId;
		float opacity;
		bool visible;
	};

	Sprite *drawSprite(const Transform *pTransform);
	void delSprite(Sprite *pSprite);
	void delAllSprites();

	void setCameraTransform(const Transform *pTransform);

	void resize(int w, int h);
	void render() const;

	glm::vec2 windowToClipSpace(const glm::ivec2& windowCoords) const;
	glm::vec2 windowToWorldSpace(const glm::ivec2& windowCoords, LayerId layerId) const;

private:
	using SpriteList = std::list<Sprite*>;
	using RenderMethod = void (Renderer::*)(const SpriteList&) const;

	SpriteList m_sprites;
	mutable glm::mat4x4 m_cachedPMatrix, m_cachedPMatrixInv, m_cachedVPMatrix, m_cachedVPMatrixInv;
	mutable glm::ivec4 m_cachedViewport;
	mutable glm::ivec2 m_cachedWindowSize;
	const Transform *m_pCameraTransform;

	static const float s_viewportAspect;
	static const RenderMethod s_renderMethods[LayerId_Count];

	static const float s_quadAttributes[];
	static const unsigned int s_quadIndices[];
	static GLuint s_vertexBuffer, s_indexBuffer;

	static const char s_vertexShaderString[];
	static const char s_fragmentShaderString[];
	static GLuint s_program, s_vertexShader, s_fragmentShader;
	static GLint s_attribPosLoc, s_attribTexCoordLoc;
	static GLint s_uniformMVPMatrixLoc, s_uniformTexMatrixLoc, s_uniformTextureLoc;

	static const std::vector<std::string> s_textureFilenames;
	static const int s_textureIndexes[TextureId_Count];
	static const std::pair<glm::ivec2, glm::ivec2> s_textureCoords[TextureId_Count];
	static std::vector<glm::ivec2> s_textureSizes;
	static std::vector<GLuint> s_textureIds;

	Renderer();
	~Renderer();

	void renderBackground(const SpriteList& list) const;
	void renderObjects(const SpriteList& list) const;
	void renderGui(const SpriteList& list) const;

	static GLuint loadShader(GLenum type, const char *shaderStr, std::string& log);
	static GLuint loadProgram(GLuint vShader, GLuint fShader, std::string& log);
	static glm::mat4x4 calcTextureMatrix(TextureId textureId);

	friend class RenderWidget;
};

#endif // RENDERER_H
