#include "mathutils.h"
#include "renderer.h"
#include "graphicsscene.h"
#include "graphicsobject.h"
#include "gameabstractscene.h"
#include "gameobjecttext.h"

void GameObjectText::setTransform(const Transform& value)
{
    GameObject::setTransform(value);
    rebuild();
}

const std::string &GameObjectText::text() const
{
    return m_text;
}

void GameObjectText::setText(const std::string &str)
{
    m_text = str;
    rebuild();
}

float GameObjectText::size() const
{
    return m_size;
}

void GameObjectText::setSize(const float sz)
{
    m_size = sz;
	rebuild();
}

void GameObjectText::setCentering(float x, float y)
{
	m_centeringX = x;
	m_centeringY = y;
	rebuild();
}

float GameObjectText::centeringX() const
{
	return m_centeringX;
}

float GameObjectText::centeringY() const
{
	return m_centeringY;
}

GameObjectText::GameObjectText(GameAbstractScene* pScene, const std::string& str) :
    GameObject(pScene),
    m_text(str),
	m_size(0.2f),
	m_centeringX(0.0f),
	m_centeringY(0.0f)
{
    rebuild();
}

GameObjectText::~GameObjectText()
{
    for (auto pTr: m_symbolTransforms)
        delete pTr;
}

void GameObjectText::destroy()
{
    for (auto p: m_graphicsObjects)
        m_pScene->graphicsScene()->delObject(p);
    m_graphicsObjects.clear();

    for (auto p: m_symbolTransforms)
        delete p;
    m_symbolTransforms.clear();
}

void GameObjectText::rebuild()
{
    destroy();

	glm::vec2 symPos(0.0f, -0.5f * m_size);
	float maxWidth = 0.0f, maxHeight = m_size;
    for (auto c: m_text) {
        switch (c) {
        case ' ': {
			symPos.x += 0.5f*m_size;
            break;
        }
        case '\n': {
			symPos.x = 0.0f;
			symPos.y -= m_size;
			maxHeight += m_size;
            break;
        }
        case '\t': {
            symPos.x += 4 * 0.5f * m_size;
            break;
        }
        default: {
            auto textureId = symbolToTextureId(c);
            auto textureSize = Renderer::textureSizeInfo(textureId);
            float symWidth = m_size * (float)textureSize.x / (float)textureSize.y;

            symPos.x += 0.5f * symWidth;
			Transform *pTr = new Transform(symPos, 0.0f);
            symPos.x += 0.5f * symWidth;

            auto pGraphicsObject = m_pScene->graphicsScene()->addObject(pTr);
            pGraphicsObject->setLayer(LayerId_TransparentObjects);
            pGraphicsObject->setSize(glm::vec2(symWidth, m_size));
            pGraphicsObject->setTexture(textureId);
            m_graphicsObjects.push_back(pGraphicsObject);
            m_symbolTransforms.push_back(pTr);
            break;
        }
        }
		if (symPos.x > maxWidth)
			maxWidth = symPos.x;
    }

	symPos.x = m_centeringX * maxWidth;
	symPos.y = -m_centeringY * maxHeight;
	for (auto pTr: m_symbolTransforms) {
		pTr->pos -= symPos;
		pTr->pos = toWorldSpace(m_pTransform, pTr->pos);
		pTr->angle = m_pTransform->angle;
	}


}
