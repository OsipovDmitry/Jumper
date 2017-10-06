#include <fstream>
#include <array>
#include <cstdio>

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
#include "gamecontroller.h"
#include "gameobjectbackground.h"
#include "gameobjectbrick.h"
#include "gameobjectbrokenbrick.h"
#include "gameobjectplayer.h"
#include "gameobjectguibutton.h"
#include "gameobjectgun.h"
#include "gameobjectlevelpassed.h"
#include "gamescenelevel.h"
#include "gamescenegameover.h"
#include "gameobjectmodifierrotate.h"
#include "gameobjectmodifieroffset.h"
#include "gameobjectmodifiertrain.h"

namespace {
	static const std::string s_maxOpenedlevelFilename = "savefile";
}

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

	if (m_pPlayer->transform().pos.y < GLOBAL_DOWN)
		Core::getController<GameController>()->sendMessage(new GameChangeSceneMessage(GameSceneId_GameOver, new GameSceneGameOver::ActivateData(m_currentLevelId)));
}

void GameSceneLevel::mouseClick(int32_t x, int32_t y)
{
	ObjectsList list = selectObjects(x, y);

	//
}

void GameSceneLevel::activate(AbstractActivateData*)
{
	m_pPlayer->physicsBody()->setVelocity(glm::vec2());
}

GameSceneLevel::GameSceneLevel() :
	GameAbstractScene(),
	m_gameObjects(),
	m_currentLevelId(GameLevelId_None)
{
	physicsScene()->setGravity(glm::vec2(0.0f, -5.0f));

	m_pPlayer = createGameObject<GameObjectPlayer>();
}

GameSceneLevel::~GameSceneLevel()
{
}

bool GameSceneLevel::load(GameLevelId levelId)
{
	static const auto s_rootNodeName = "level";

	static const auto s_backgroundNodeName = "background";
	static const auto s_playerNodeName = "player";
	static const auto s_objectNodeName = "object";

	static const auto s_objectTypeAttr = "type";

	static const auto s_objectTypeBrick = "brick";
	static const auto s_objectTypeBrokenBrick = "broken_brick";
	static const auto s_objectTypeLevelPassed = "level_passed";
	static const auto s_objectTypeGun = "gun";

	static const auto s_objectModifierNodeName = "mod";
	static const auto s_objectModifierTypeAttr = "type";

	static const auto s_objectModifierTypeOffset = "offset";

	unload();
	std::string filename = levelIdToFilename(levelId);

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

	m_currentLevelId = levelId;

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
				else if (!strcmp(pType->value(), s_objectTypeLevelPassed))
					pGameObject = createGameObject<GameObjectLevelPassed>(m_currentLevelId);
				else if (!strcmp(pType->value(), s_objectTypeGun))
					pGameObject = createGameObject<GameObjectGun>();

				m_gameObjects.push_back(pGameObject);
			}
		}

		if (pGameObject) {
			for (auto attr = pNode->first_attribute(); attr; attr = attr->next_attribute())
				pGameObject->setParam(attr->name(), attr->value());

			for (auto pObjMod = pNode->first_node(); pObjMod; pObjMod = pObjMod->next_sibling()) {
				if (!strcmp(pObjMod->name(), s_objectModifierNodeName)) {
					auto pType = pObjMod->first_attribute(s_objectModifierTypeAttr);
					GameObjectAbstractModifier *pModifier;
					if (pType) {
						if (!strcmp(pType->value(), s_objectModifierTypeOffset))
							pModifier = pGameObject->addModifier<GameObjectModifierOffset>();
					}
					if (pModifier) {
						for (auto attr = pObjMod->first_attribute(); attr; attr = attr->next_attribute())
							pModifier->setParam(attr->name(), attr->value());
					}
				}
			}
		}

		pNode = pNode->next_sibling();
	}
	return true;
}

void GameSceneLevel::unload()
{
	for (auto pObject: m_gameObjects)
		delObject(pObject);
	m_gameObjects.clear();
	m_currentLevelId = GameLevelId_None;
}

GameLevelId GameSceneLevel::currentLevel() const
{
	return m_currentLevelId;
}

GameLevelId GameSceneLevel::maxOpenedLevel()
{
	FILE *pFile = fopen(s_maxOpenedlevelFilename.c_str(), "r");
	if (!pFile)
		return GameLevelId_1;
	int id;
	fscanf(pFile, "%d", &id);
	fclose(pFile);
	return static_cast<GameLevelId>(id);
}

void GameSceneLevel::setMaxOpenedLevel(GameLevelId levelId)
{
	if (levelId >= maxOpenedLevel()) {
		FILE *pFile = fopen(s_maxOpenedlevelFilename.c_str(), "w");
		if (!pFile)
			return;
		fprintf(pFile, "%d", static_cast<GameLevelId>(levelId));
		fclose(pFile);
	}
}

std::string GameSceneLevel::levelIdToFilename(GameLevelId levelId)
{
	static const std::array<std::string, GameLevelId_Count> table = {
		"level1.xml",
		"level2.xml",
		"level3.xml"
	};

	return table[levelId];
}
