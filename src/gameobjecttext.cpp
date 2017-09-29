#include "mathutils.h"
#include "graphicsscene.h"
#include "graphicsobject.h"
#include "gameabstractscene.h"
#include "gameobjecttext.h"

void GameObjectText::setTransform(const Transform& value)
{
	GameObject::setTransform(value);
	//
}

GameObjectText::GameObjectText(GameAbstractScene* pScene, const std::string& str) :
	GameObject(pScene)
{
	static const float symSize = 0.2f;
	glm::vec2 symPos = m_pTransform->pos + 0.5f * glm::vec2(symSize, -symSize);
	for (auto c: str) {
		switch (c) {
			case ' ': {
				symPos.x += symSize;
				break;
			}
			case '\n': {
				symPos.x = m_pTransform->pos.x + 0.5f * symSize;
				symPos.y -= symSize;
				break;
			}
			case '\t': {
				symPos.x += 4 * symSize;
				break;
			}
			default: {
				Transform *pTr = new Transform(*m_pTransform);
				pTr->pos = symPos;
				auto pGraphicsObject = pScene->graphicsScene()->addObject(pTr);
				pGraphicsObject->setLayer(LayerId_TransparentObjects);
				pGraphicsObject->setSize(glm::vec2(symSize, symSize));
				pGraphicsObject->setTexture(symbolToTextureId(c));
				m_graphicsObjects.push_back(pGraphicsObject);
				m_symbolTransforms.push_back(pTr);
				symPos.x += symSize;
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
