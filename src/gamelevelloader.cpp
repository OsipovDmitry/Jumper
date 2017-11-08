#include <array>

#include <QFile>

#include "rapidxml/rapidxml.hpp"

#include "gamelevelloader.h"
#include "gamescenelevel.h"
#include "gameobjectbrick.h"
#include "gameobjectbrokenbrick.h"
#include "gameobjectgun.h"
#include "gameobjectbackground.h"
#include "gameobjectplayer.h"
#include "gameobjectlevelpassed.h"
#include "gameobjectmodifieroffset.h"

GameLevelLoader::GameLevelLoader(GameSceneLevel* pTargetLevel) :
	m_pTargetLevel(pTargetLevel)
{

}

bool GameLevelLoader::load(GameLevelId levelId)
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
	std::string buffer;

	QFile file(QString::fromStdString(filename));
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;
	buffer = file.readAll().toStdString();
	file.close();
	buffer.push_back('\0');

	rapidxml::xml_document<> doc;
	try {
		doc.parse<0>(&(buffer[0]));
	} catch (const rapidxml::parse_error&) {
		return false;
	}
	auto pRootNode = doc.first_node();
	if (!pRootNode)
		return false;
	if (strcmp(pRootNode->name(), s_rootNodeName))
		return false;

	m_pTargetLevel->m_currentLevelId = levelId;

	auto pNode = pRootNode->first_node();
	while (pNode) {
		GameObject *pGameObject = nullptr;
		if (!strcmp(pNode->name(), s_backgroundNodeName)) {
			pGameObject = m_pTargetLevel->m_pBackgroundObject;
		}
		else if (!strcmp(pNode->name(), s_playerNodeName)) {
			pGameObject = m_pTargetLevel->m_pPlayer;
		}
		else if (!strcmp(pNode->name(), s_objectNodeName)) {
			auto pType = pNode->first_attribute(s_objectTypeAttr);
			if (pType) {
				if (!strcmp(pType->value(), s_objectTypeBrick))
					pGameObject = m_pTargetLevel->createGameObject<GameObjectBrick>();
				else if (!strcmp(pType->value(), s_objectTypeBrokenBrick))
					pGameObject = m_pTargetLevel->createGameObject<GameObjectBrokenBrick>();
				else if (!strcmp(pType->value(), s_objectTypeLevelPassed))
					pGameObject = m_pTargetLevel->createGameObject<GameObjectLevelPassed>(
									  m_pTargetLevel->m_currentLevelId);
				else if (!strcmp(pType->value(), s_objectTypeGun))
					pGameObject = m_pTargetLevel->createGameObject<GameObjectGun>();

				m_pTargetLevel->m_gameObjects.push_back(pGameObject);
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

void GameLevelLoader::unload()
{
	m_pTargetLevel->m_pPlayer->resetVelocity();
	for (auto pObject: m_pTargetLevel->m_gameObjects)
		m_pTargetLevel->delGameObject(pObject);
	m_pTargetLevel->m_gameObjects.clear();
	m_pTargetLevel->m_currentLevelId = GameLevelId_None;
}

std::string GameLevelLoader::levelIdToFilename(GameLevelId levelId)
{
	static const std::array<std::string, GameLevelId_Count> table = {
		":/res/level1.xml",
		":/res/level2.xml",
		":/res/level3.xml"
	};

	return table[levelId];
}
