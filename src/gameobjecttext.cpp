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

GameObjectText::GameObjectText(GameAbstractScene* pScene, const std::string& str, const float textSize) :
    GameObject(pScene),
    m_text(str),
    m_size(textSize)
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

    glm::vec2 symPos = m_pTransform->pos + 0.5f * glm::vec2(0.0f, -m_size);
    for (auto c: m_text) {
        switch (c) {
        case ' ': {
            symPos.x += 0.5f*m_size;
            break;
        }
        case '\n': {
            symPos.x = m_pTransform->pos.x;
            symPos.y -= m_size;
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
            Transform *pTr = new Transform(*m_pTransform);
            pTr->pos = symPos;
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
    }
}
