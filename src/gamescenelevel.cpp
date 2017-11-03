#include <array>

#include <QFile>

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
#include "audiocontroller.h"
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
#include "gamescenepause.h"
#include "gameobjectmodifierrotate.h"
#include "gameobjectmodifieroffset.h"
#include "gameobjectmodifiertrain.h"

namespace {
	static const std::string s_maxOpenedlevelFilename = "savefile";
}

void GameSceneLevel::update(uint32_t dt)
{
	auto pGameController = Core::getController<GameController>();
	if (!pGameController)
		return;

	auto pAudioController = Core::getController<AudioController>();
	if (!pAudioController)
		return;

	Transform transform = m_pPlayer->transform();

	if (pGameController->keyState(KeyCode_Left))
		transform.pos.x -= 3.0f * 0.001f * dt;
	if (pGameController->keyState(KeyCode_Right))
		transform.pos.x += 3.0f * 0.001f * dt;

	static const float minTilt = 5.0f;
	static const float maxTilt = 20.0f;
	float tilt = pGameController->tiltState().y;
	int tiltSign = glm::sign(tilt);
	tilt = glm::clamp(glm::abs(tilt), minTilt, maxTilt);
	tilt = (tilt - minTilt) / (maxTilt - minTilt);
	transform.pos.x += 3.0f * 0.001f * dt * tiltSign * tilt;

	m_pPlayer->setTransform(transform);

	graphicsScene()->camera()->transform()->pos.x = transform.pos.x;
	pAudioController->setListenerPosition(transform.pos);

	if (m_pPlayer->transform().pos.y < GLOBAL_DOWN) {
		pGameController->sendMessage(new GameChangeSceneMessage(GameSceneId_GameOver, new GameSceneGameOver::ActivateData(m_currentLevelId)));
		pAudioController->playSound(SoundId_GameOver, nullptr);
	}
}

void GameSceneLevel::mouseClick(int32_t x, int32_t y)
{
	ObjectsList list = selectObjects(x, y);

	auto pGameController = Core::getController<GameController>();
	if (!pGameController)
		return;

	if (std::find(list.cbegin(), list.cend(), m_pPauseButton) != list.cend()) {
		pGameController->sendMessage(new GameChangeSceneMessage(GameSceneId_Pause, new GameScenePause::ActivateData(m_currentLevelId)));
	}
}

void GameSceneLevel::activate(AbstractActivateData*)
{
#if defined(Q_OS_ANDROID)
	Core::getController()->renderWidget()->calibrateTiltSensor();
#elif defined(Q_OS_LINUX) || defined(Q_OS_WIN)
#else
#endif
}

GameSceneLevel::GameSceneLevel() :
	GameAbstractScene(),
	m_gameObjects(),
	m_currentLevelId(GameLevelId_None)
{
	physicsScene()->setGravity(glm::vec2(0.0f, -5.0f));

	m_pPlayer = createGameObject<GameObjectPlayer>();

	m_pPauseButton = createGameObject<GameObjectGuiButton>(GuiButtonId_Pause);
	m_pPauseButton->setTransform(Transform(glm::vec2(-1.4f, 0.8f)));
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
	m_pPlayer->physicsBody()->setVelocity(glm::vec2());
	for (auto pObject: m_gameObjects)
		delGameObject(pObject);
	m_gameObjects.clear();
	m_currentLevelId = GameLevelId_None;
}

GameLevelId GameSceneLevel::currentLevel() const
{
	return m_currentLevelId;
}

GameLevelId GameSceneLevel::maxOpenedLevel()
{
	QFile file(QString::fromStdString(s_maxOpenedlevelFilename));
	if (!file.open(QIODevice::ReadOnly))
		return GameLevelId_1;
	GameLevelId id = GameLevelId_1;
	file.read(reinterpret_cast<char*>(&id), sizeof(GameLevelId));
	file.close();
	return id;
}

void GameSceneLevel::setMaxOpenedLevel(GameLevelId levelId)
{
	if (levelId >= maxOpenedLevel()) {
		QFile file(QString::fromStdString(s_maxOpenedlevelFilename));
		if (!file.open(QIODevice::WriteOnly))
			return;
		file.write(reinterpret_cast<const char*>(&levelId), sizeof(GameLevelId));
		file.close();
	}
}

std::string GameSceneLevel::levelIdToFilename(GameLevelId levelId)
{
	static const std::array<std::string, GameLevelId_Count> table = {
		":/res/level1.xml",
		":/res/level2.xml",
		":/res/level3.xml"
	};

	return table[levelId];
}
