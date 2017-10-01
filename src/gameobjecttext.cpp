#include "mathutils.h"
#include "renderer.h"
#include "graphicsscene.h"
#include "graphicsobject.h"
#include "gameabstractscene.h"
#include "gameobjecttext.h"

void GameObjectText::setTransform(const Transform& value)
{
	GameObject::setTransform(value);
	//
}

GameObjectText::GameObjectText(GameAbstractScene* pScene, const std::string& str, const float textSize) :
	GameObject(pScene)
{
    m_pTransform->pos.x = -1;
    glm::vec2 symPos = m_pTransform->pos + 0.5f * glm::vec2(0.0f, -textSize);
	for (auto c: str) {
		switch (c) {
			case ' ': {
                symPos.x += textSize;
				break;
			}
			case '\n': {
                symPos.x = m_pTransform->pos.x;
                symPos.y -= textSize;
				break;
			}
			case '\t': {
                symPos.x += 4 * textSize;
				break;
			}
			default: {
                auto textureId = symbolToTextureId(c);
                auto textureSize = Renderer::textureSizeInfo(textureId);
                float symAspect = (float)textureSize.x / (float)textureSize.y;

                symPos.x += 0.5f * textSize*symAspect;
				Transform *pTr = new Transform(*m_pTransform);
				pTr->pos = symPos;
                symPos.x += 0.5f * textSize*symAspect;

				auto pGraphicsObject = pScene->graphicsScene()->addObject(pTr);
				pGraphicsObject->setLayer(LayerId_TransparentObjects);
                pGraphicsObject->setSize(glm::vec2(textSize*symAspect, textSize));
                pGraphicsObject->setTexture(textureId);
				m_graphicsObjects.push_back(pGraphicsObject);
                m_symbolTransforms.push_back(pTr);
				break;
			}
		}
	}
}

GameObjectText::~GameObjectText()
{
	for (auto pTr: m_symbolTransforms)
		delete pTr;
}
