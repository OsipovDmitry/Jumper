#include <utility>
#include <algorithm>
#ifdef JUMPER_DEBUG
#include <iostream>
#endif

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <QImage>

#include "renderer.h"

const float Renderer::s_viewportAspect = 16.0f / 9.0f;
const Renderer::RenderMethod Renderer::s_renderMethods[LayerId_Count] = {
	&Renderer::renderBackground,
	&Renderer::renderObjects,
	&Renderer::renderGui,
};

const float Renderer::s_quadAttributes[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, // left down
	+0.5f, -0.5f, 1.0f, 1.0f, // right down
	+0.5f, +0.5f, 1.0f, 0.0f, // right top
	-0.5f, +0.5f, 0.0f, 0.0f, // left top
};
const unsigned int Renderer::s_quadIndices[] = {
	0, 1, 2,
	0, 2, 3
};
GLuint Renderer::s_vertexBuffer, Renderer::s_indexBuffer;

const char Renderer::s_vertexShaderString[] =
	"attribute vec2 vPosition;\n"
	"attribute vec2 vTexcoord;\n"
	"uniform mat4 mvpMatrix;\n"
	"uniform mat4 textureMatrix;\n"
	"varying vec2 tex_coord;\n"
	"void main()\n"
	"{\n"
	"	tex_coord = (textureMatrix * vec4(vTexcoord, 0.0, 1.0)).xy;\n"
	"	gl_Position = mvpMatrix * vec4(vPosition, 0.0, 1.0);\n"
	"}\n";
const char Renderer::s_fragmentShaderString[] =
	//"precision mediump float;\n"
	"uniform sampler2D texture;\n"
	"varying vec2 tex_coord;\n"
	"void main()\n"
	"{\n"
	"	vec4 outColor = texture2D(texture, tex_coord);\n"
	"	if (outColor.a < 0.01) discard;\n"
	"	gl_FragColor = outColor;\n"
	"}\n";
GLuint Renderer::s_program, Renderer::s_vertexShader, Renderer::s_fragmentShader;
GLint Renderer::s_attribPosLoc, Renderer::s_attribTexCoordLoc;
GLint Renderer::s_uniformMVPMatrixLoc, Renderer::s_uniformTexMatrixLoc, Renderer::s_uniformTextureLoc;

const std::vector<std::string> Renderer::s_textureFilenames {
        std::string("texture0.png"),
        std::string("texture1.png"),
	};
const int Renderer::s_textureIndexes[TextureId_Count] = {
	0, // TextureId_None,
	0, // TextureId_Brick
	0, // TextureId_Circle
	0, // TextureId_Rect
	0, // TextureId_BrokenBrick
	0, // TextureId_BrokenBrickPart
	0, // TextureId_ButtonStart
	0, // TextureId_ButtonExit
	0, // TextureId_ButtonEmpty
	0, // TextureId_Gun
	1, // TextureId_Background0
};
const std::pair<glm::ivec2, glm::ivec2> Renderer::s_textureCoords[TextureId_Count] = {
	std::make_pair(glm::ivec2(0+1,0+1), glm::ivec2(32-2,32-2)), // TextureId_None,
	std::make_pair(glm::ivec2(32+1,0+1), glm::ivec2(96-2,32-2)), // TextureId_Brick,
	std::make_pair(glm::ivec2(128+1,0+1), glm::ivec2(32-2,32-2)), // TextureId_Circle,
	std::make_pair(glm::ivec2(160+1,0+1), glm::ivec2(32-2,32-2)), // TextureId_Rect,
	std::make_pair(glm::ivec2(192+1,0+1), glm::ivec2(96-2,32-2)), // TextureId_BrokenBrick,
	std::make_pair(glm::ivec2(288+1,0+1), glm::ivec2(32-2,32-2)), // TextureId_BrokenBrickPart,
	std::make_pair(glm::ivec2(0+1,32+1), glm::ivec2(128-2, 64-2)), // TextureId_ButtonStart,
	std::make_pair(glm::ivec2(128+1,32+1), glm::ivec2(128-2, 64-2)), // TextureId_ButtonExit,
	std::make_pair(glm::ivec2(256+1,32+1), glm::ivec2(128-2, 64-2)), // TextureId_ButtonEmpty,
	std::make_pair(glm::ivec2(0+1,96+1), glm::ivec2(128-2, 64-2)), // TextureId_Gun,
	std::make_pair(glm::ivec2(0,0+1), glm::ivec2(1024,128-2)), // TextureId_Background0,
};
std::vector<glm::ivec2> Renderer::s_textureSizes;
std::vector<GLuint> Renderer::s_textureIds;

Renderer::Sprite *Renderer::drawSprite(const Transform* pTransform)
{
	Sprite *pSprite = new Sprite;
	pSprite->pTransform = pTransform;
	pSprite->layerId = LayerId_Objects;
	pSprite->opacity = 1.0f;
	pSprite->size = glm::vec2(1.5f, 1.0f);
	pSprite->textureId = TextureId_None;
	pSprite->visible = true;

	m_sprites.push_back(pSprite);
	return pSprite;
}

void Renderer::delSprite(Sprite* pSprite)
{
	SpriteList::iterator it = std::find(m_sprites.begin(), m_sprites.end(), pSprite);
	if (it != m_sprites.end())
		m_sprites.erase(it);
}

void Renderer::delAllSprites()
{
	for (SpriteList::iterator it = m_sprites.begin(); it != m_sprites.end(); delete *(it++));
	m_sprites.clear();
}

void Renderer::setCameraTransform(const Transform* pTransform)
{
	m_pCameraTransform = pTransform;
}

void Renderer::resize(int w, int h)
{
	m_cachedWindowSize = glm::ivec2(w, h);
	if (w >= s_viewportAspect * h) {
		m_cachedViewport[2] = s_viewportAspect * h;
		m_cachedViewport[3] = h;
		m_cachedViewport[0] = (w - m_cachedViewport[2]) / 2;
		m_cachedViewport[1] = 0;
	}
	else {
		m_cachedViewport[2] = w;
		m_cachedViewport[3] = w / s_viewportAspect;
		m_cachedViewport[0] = 0;
		m_cachedViewport[1] = (h-m_cachedViewport[3]) / 2;
	}
	glViewport(m_cachedViewport[0], m_cachedViewport[1], m_cachedViewport[2], m_cachedViewport[3]);
}

void Renderer::render() const
{
	m_cachedVPMatrix = m_cachedPMatrix;
	if (m_pCameraTransform)
		m_cachedVPMatrix *= glm::translate(glm::mat4x4(), -glm::vec3(m_pCameraTransform->pos, 0.0f));
	m_cachedVPMatrixInv = glm::inverse(m_cachedVPMatrix);

	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	SpriteList lists[LayerId_Count];

	for (SpriteList::const_iterator it = m_sprites.cbegin(); it != m_sprites.cend(); ++it)
		if ((*it)->visible)
			lists[(*it)->layerId].push_back(*it);

	glBindBuffer(GL_ARRAY_BUFFER, s_vertexBuffer);
	glVertexAttribPointer(s_attribPosLoc, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (const void*)(0*sizeof(float)));
	glEnableVertexAttribArray(s_attribPosLoc);
	glVertexAttribPointer(s_attribTexCoordLoc, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (const void*)(2*sizeof(float)));
	glEnableVertexAttribArray(s_attribTexCoordLoc);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_indexBuffer);

	glUseProgram(s_program);
	glUniform1i(s_uniformTextureLoc, 0);

	for (int layerId = 0; layerId < LayerId_Count; ++layerId) {
		(this->*s_renderMethods[layerId])(lists[layerId]);
	}
}

glm::vec2 Renderer::windowToClipSpace(const glm::ivec2& windowCoords) const
{
	return 2.0f *
			((glm::vec2(windowCoords.x, m_cachedWindowSize.y-windowCoords.y) -
			  glm::vec2(m_cachedViewport.x, m_cachedViewport.y)) /
			 glm::vec2(m_cachedViewport.z, m_cachedViewport.w)) -
			glm::vec2(1.0f);
}

glm::vec2 Renderer::windowToWorldSpace(const glm::ivec2& windowCoords, LayerId layerId) const
{
	glm::vec4 worldCoords, clipCoords = glm::vec4(windowToClipSpace(windowCoords), 0.0f, 1.0f);
	switch (layerId) {
		case LayerId_Background: { worldCoords = clipCoords; break; }
		case LayerId_Objects: { worldCoords = m_cachedVPMatrixInv * glm::vec4(windowToClipSpace(windowCoords), 0.0f, 1.0f); break; }
		case LayerId_Gui: { worldCoords = m_cachedPMatrixInv * glm::vec4(windowToClipSpace(windowCoords), 0.0f, 1.0f); break; }
		default: { worldCoords = glm::vec4(); break; }
	}
	return glm::vec2(worldCoords);
}

Renderer::Renderer() :
	m_sprites(),
	m_cachedPMatrix(glm::ortho(-s_viewportAspect, +s_viewportAspect, -1.0f, +1.0f)),
	m_cachedPMatrixInv(glm::inverse(m_cachedPMatrix)),
	m_cachedVPMatrix(),
	m_cachedVPMatrixInv(),
	m_cachedViewport(),
	m_pCameraTransform(nullptr)
{
	glGenBuffers(1, &s_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, s_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(s_quadAttributes), static_cast<const void*>(s_quadAttributes), GL_STATIC_DRAW);
	glGenBuffers(1, &s_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(s_quadIndices), static_cast<const void*>(s_quadIndices), GL_STATIC_DRAW);

	std::string log;
	log.clear();
	s_vertexShader = loadShader(GL_VERTEX_SHADER, s_vertexShaderString, log);
#ifdef JUMPER_DEBUG
	if (!log.empty())
		std::cout << "Vertex shader: " << log << std::endl;
#endif
	log.clear();
	s_fragmentShader = loadShader(GL_FRAGMENT_SHADER, s_fragmentShaderString, log);
#ifdef JUMPER_DEBUG
	if (!log.empty())
		std::cout << "Fragment shader: " << log << std::endl;
#endif
	log.clear();
	s_program = loadProgram(s_vertexShader, s_fragmentShader, log);
#ifdef JUMPER_DEBUG
	if (!log.empty())
		std::cout << "Program: " << log << std::endl;
#endif
	s_attribPosLoc = glGetAttribLocation(s_program, "vPosition");
	s_attribTexCoordLoc = glGetAttribLocation(s_program, "vTexcoord");
	s_uniformMVPMatrixLoc = glGetUniformLocation(s_program, "mvpMatrix");
	s_uniformTexMatrixLoc = glGetUniformLocation(s_program, "textureMatrix");
	s_uniformTextureLoc = glGetUniformLocation(s_program, "texture");

	int numTextures = s_textureFilenames.size();
	s_textureIds.resize(numTextures);
	s_textureSizes.resize(numTextures);
	for (int i = 0; i < numTextures; ++i) {
		QImage image;
		if (!image.load(QString::fromStdString(s_textureFilenames[i]))) {
			s_textureIds[i] = 0;
			continue;
		}
		image = image.convertToFormat(QImage::Format_RGBA8888);
		s_textureSizes[i] = glm::ivec2(image.width(), image.height());
		glGenTextures(1, &(s_textureIds[i]));
		glBindTexture(GL_TEXTURE_2D, s_textureIds[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
	}
}

Renderer::~Renderer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &s_vertexBuffer);

	glUseProgram(0);
	glDetachShader(s_program, s_vertexShader);
	glDetachShader(s_program, s_fragmentShader);
	glDeleteShader(s_vertexShader);
	glDeleteShader(s_fragmentShader);
	glDeleteProgram(s_program);

	glBindTexture(GL_TEXTURE_2D, 0);
	for (auto& id: s_textureIds)
		glDeleteTextures(1, &id);
}

void Renderer::renderBackground(const Renderer::SpriteList& list) const
{
	for (SpriteList::const_iterator it = list.cbegin(); it != list.cend(); ++it) {
		Sprite *p = *it;

		glm::mat4x4 mvpMatrix = glm::translate(glm::mat4x4(), glm::vec3(p->pTransform->pos, 0.0f)) *
								glm::rotate(glm::mat4x4(), p->pTransform->angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
								glm::scale(glm::mat4x4(), glm::vec3(p->size, 1.0f));

		const float texScale = (float)s_textureCoords[p->textureId].second.y /
							  (float)s_textureCoords[p->textureId].second.x *
							  s_viewportAspect;

		glm::mat4x4 textureMatrix = calcTextureMatrix(p->textureId) *
									glm::scale(glm::mat4x4(), glm::vec3(texScale, 1.0f, 1.0f)) *
									glm::translate(glm::mat4x4(), glm::vec3(m_pCameraTransform->pos.x/s_viewportAspect/2.0f, 0.0f, 0.0f));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, s_textureIds[s_textureIndexes[p->textureId]]);

		glUniformMatrix4fv(s_uniformMVPMatrixLoc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
		glUniformMatrix4fv(s_uniformTexMatrixLoc, 1, GL_FALSE, glm::value_ptr(textureMatrix));

		glDrawElements(GL_TRIANGLES, sizeof(s_quadIndices)/sizeof(float), GL_UNSIGNED_INT, 0);
	}
}

void Renderer::renderObjects(const Renderer::SpriteList& list) const
{
	glEnable(GL_ALPHA);
	for (SpriteList::const_iterator it = list.cbegin(); it != list.cend(); ++it) {
		Sprite *p = *it;

		glm::mat4x4 mvpMatrix = m_cachedVPMatrix *
								  glm::translate(glm::mat4x4(), glm::vec3(p->pTransform->pos, 0.0f)) *
								  glm::rotate(glm::mat4x4(), p->pTransform->angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
								  glm::scale(glm::mat4x4(), glm::vec3(p->size, 1.0f));

		glm::mat4x4 textureMatrix = calcTextureMatrix(p->textureId);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, s_textureIds[s_textureIndexes[p->textureId]]);

		glUniformMatrix4fv(s_uniformMVPMatrixLoc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
		glUniformMatrix4fv(s_uniformTexMatrixLoc, 1, GL_FALSE, glm::value_ptr(textureMatrix));

		glDrawElements(GL_TRIANGLES, sizeof(s_quadIndices)/sizeof(float), GL_UNSIGNED_INT, 0);
	}
}

void Renderer::renderGui(const Renderer::SpriteList& list) const
{
	for (SpriteList::const_iterator it = list.cbegin(); it != list.cend(); ++it) {
		Sprite *p = *it;

		glm::mat4x4 mvpMatrix = m_cachedPMatrix *
								  glm::translate(glm::mat4x4(), glm::vec3(p->pTransform->pos, 0.0f)) *
								  glm::rotate(glm::mat4x4(), p->pTransform->angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
								  glm::scale(glm::mat4x4(), glm::vec3(p->size, 1.0f));

		glm::mat4x4 textureMatrix = calcTextureMatrix(p->textureId);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, s_textureIds[s_textureIndexes[p->textureId]]);

		glUniformMatrix4fv(s_uniformMVPMatrixLoc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
		glUniformMatrix4fv(s_uniformTexMatrixLoc, 1, GL_FALSE, glm::value_ptr(textureMatrix));

		glDrawElements(GL_TRIANGLES, sizeof(s_quadIndices)/sizeof(float), GL_UNSIGNED_INT, 0);
	}
}


GLuint Renderer::loadShader(GLenum type, const char* shaderStr, std::string& log)
{
	GLuint shader = glCreateShader(type);
	if (shader == 0)
	   return 0;
	glShaderSource(shader, 1, &shaderStr, NULL);
	glCompileShader(shader);
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
	   GLint infoLen = 0;
	   glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
	   if(infoLen > 1) {
		  char *infoLog = (char*)malloc(sizeof(char) * infoLen);
		  glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
		  log = infoLog;
		  free(infoLog);
	   }
	   glDeleteShader(shader);
	   return 0;
	}
	return shader;
}

GLuint Renderer::loadProgram(GLuint vShader, GLuint fShader, std::string& log)
{
	GLuint programObject = glCreateProgram();
	if (programObject == 0)
	   return 0;
	glAttachShader(programObject, vShader);
	glAttachShader(programObject, fShader);
	glLinkProgram(programObject);
	GLint linked;
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	if (!linked) {
	   GLint infoLen = 0;
	   glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
	   if(infoLen > 1) {
		  char *infoLog = (char*)malloc(sizeof(char) * infoLen);
		  glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
		  log = infoLog;
		  free(infoLog);
	   }
	   glDeleteProgram(programObject);
	   return 0;
	}
	return programObject;
}

glm::mat4x4 Renderer::calcTextureMatrix(TextureId textureId)
{
	glm::vec2 atlasSize = (glm::vec2)s_textureSizes[s_textureIndexes[textureId]];
	glm::vec2 texPos = (glm::vec2)s_textureCoords[textureId].first;
	glm::vec2 texSize = (glm::vec2)s_textureCoords[textureId].second;

	return glm::translate(glm::mat4x4(), glm::vec3(texPos / atlasSize, 0.0f)) *
			glm::scale(glm::mat4x4(), glm::vec3(texSize / atlasSize, 1.0f));
}
