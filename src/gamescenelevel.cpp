#include <fstream>

#include "rapidxml/rapidxml.hpp"

#include "types.h"
#include "core.h"
#include "renderwidget.h"
#include "renderer.h"
#include "renderwidget.h"
#include "graphicsscene.h"
#include "graphicscamera.h"
#include "physicsscene.h"
#include "physicsbody.h"
#include "gameobjectbackground.h"
#include "gameobjectbrick.h"
#include "gameobjectbrokenbrick.h"
#include "gameobjectplayer.h"
#include "gameobjectguibutton.h"
#include "gameobjectgun.h"
#include "gamescenelevel.h"
#include "gameobjectmodifierrotate.h"
#include "gameobjectmodifieroffset.h"
#include "gameobjectmodifiertrain.h"

void GameSceneLevel::update(uint64_t time, uint32_t dt)
{
	(void)time;
	(void)dt;
	Transform transform = m_pPlayer->transform();
	if (Core::getController()->renderWidget()->testKey(RenderWidget::KeyCode_Left))
		transform.pos.x -= 0.05f;
	if (Core::getController()->renderWidget()->testKey(RenderWidget::KeyCode_Right))
		transform.pos.x += 0.05f;
	m_pPlayer->setTransform(transform);

	graphicsScene()->camera()->transform()->pos.x = transform.pos.x;
}

void GameSceneLevel::mouseClick(int32_t x, int32_t y)
{
	ObjectsList list = selectObjects(x, y);

	if (std::find(list.cbegin(), list.cend(), m_pButtonStart) != list.cend()) {
		m_pPlayer->setTransform(Transform(glm::vec2(0.0f, 0.7f), 0.0f));
		m_pPlayer->physicsBody()->setVelocity(glm::vec2(0.0f, 0.0f));
	}

	if (std::find(list.cbegin(), list.cend(), m_pButtonExit) != list.cend()) {
		Core::getController()->sendMessage(new CoreExitMessage());
	}
}

GameSceneLevel::GameSceneLevel() :
	GameAbstractScene()
{
	physicsScene()->setGravity(glm::vec2(0.0f, -5.0f));

	m_pPlayer = createGameObject<GameObjectPlayer>();
	m_pPlayer->setTransform(Transform(glm::vec2(0.0f, 0.7f), 0.0f));

//	const int N = 20;
//	for (int i = 0; i < N; ++i) {
//		auto pBrick = createGameObject<GameObjectBrick>();
//		pBrick->setTransform(Transform(glm::vec2(1.375f * i, ((float)rand()/(float)RAND_MAX*2 - 1) * 0.4f - 0.5f), 0.0f));
//		if (i == 0) {
//			pBrick->setTransform(Transform(glm::vec2(0.0f, -0.7f), 0.0f));
////			auto pMod = pBrick->addModifier<GameObjectModifierTrain>();
////			pMod->keyFramesList().emplace_back(Transform(glm::vec2(-0.5f, -0.7f), 0.0f), 0.0f);
////			pMod->keyFramesList().emplace_back(Transform(glm::vec2(0.5f, -0.7f), 0.0f), 2.0f);
////			pMod->keyFramesList().emplace_back(Transform(glm::vec2(0.5f, 0.3f), 0.0f), 2.0f);
////			pMod->keyFramesList().emplace_back(Transform(glm::vec2(-0.5f, 0.3f), 0.0f), 2.0f);
////			pMod->keyFramesList().emplace_back(Transform(glm::vec2(-0.5f, -0.7f), 0.0f), 2.0f);
////			pMod->setLoop(true);
//		}

//		if ((i % 4 == 1) && (i != 1))
//			pBrick->addModifier<GameObjectModifierRotate>(3.14f / 4.0f);
//		if (i % 4 == 2)
//			pBrick->addModifier<GameObjectModifierOffset>(glm::vec2(0.0f, 1.0f), 0.5f);
//		if (i % 4 == 3)
//			pBrick->addModifier<GameObjectModifierOffset>(glm::vec2(1.0f, 0.0f), 0.5f);
//	}

//	for (int i = 0; i < 10; ++i) {
//		auto pBrick = createGameObject<GameObjectBrokenBrick>();
//		pBrick->setTransform(Transform(glm::vec2(2 + 2.1f * i, 0.0f), 0.0f));
//	}

//	GameObjectGun *pGun = createGameObject<GameObjectGun>();
//	pGun->setTransform(Transform(glm::vec2(5.5f, 0.05f), 0.0f));

//	m_pButtonStart = createGameObject<GameObjectGuiButton>(GuiButtonId_Start);
//	m_pButtonStart->setTransform(Transform(glm::vec2(-1.2f, 0.8f)));

//	m_pButtonExit = createGameObject<GameObjectGuiButton>(GuiButtonId_Exit);
//	m_pButtonExit->setTransform(Transform(glm::vec2(+1.2f, 0.8f)));

	loadFromFile("level1.xml");
}

GameSceneLevel::~GameSceneLevel()
{
}

bool GameSceneLevel::loadFromFile(const std::string& filename)
{
	static const auto s_rootNodeName = "level";
	static const auto s_backgroundNodeName = "background";
	static const auto s_playerNodeName = "player";
	static const auto s_objectNodeName = "object";
	static const auto s_objectTypeAttr = "type";
	static const auto s_objectTypeBrick = "brick";
	static const auto s_objectTypeBrokenBrick = "broken_brick";

	std::ifstream stream(filename);
	if (!stream.is_open())
		return false;

	stream.seekg(0, stream.end);
	auto length = stream.tellg();
	stream.seekg(0, stream.beg);
	std::vector<char> buffer(length+1);
	stream.read(buffer.data(),length);
	stream.close();
	buffer[length] = '\0';

	rapidxml::xml_document<> doc;
	try {
			doc.parse<0>(buffer.data());
	} catch (const rapidxml::parse_error&) {
		return false;
	}
	auto pRootNode = doc.first_node();
	if (!pRootNode)
		return false;
	if (strcmp(pRootNode->name(), s_rootNodeName))
		return false;

	auto pNode = pRootNode->first_node();
	while (pNode) {
		GameObject *pGameObject = nullptr;
		if (!strcmp(pNode->name(), s_backgroundNodeName)) {
			pGameObject = m_pBackgroundObject;
		}
		else if (!strcmp(pNode->name(), s_playerNodeName)) {
			pGameObject = m_pPlayer;
		}
		else if (!strcmp(pNode->name(), s_objectNodeName)) {
			auto pType = pNode->first_attribute(s_objectTypeAttr);
			if (pType) {
				if (!strcmp(pType->value(), s_objectTypeBrick))
					pGameObject = createGameObject<GameObjectBrick>();
				else if (!strcmp(pType->value(), s_objectTypeBrokenBrick))
					pGameObject = createGameObject<GameObjectBrokenBrick>();
			}
		}

		if (pGameObject) {
			for (auto a = pNode->first_attribute(); a; a = a->next_attribute())
				pGameObject->setParam(a->name(), a->value());
		}

		pNode = pNode->next_sibling();
	}
}
