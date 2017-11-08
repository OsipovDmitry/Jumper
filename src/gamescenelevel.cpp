#include <QFile>

#include "glm/geometric.hpp"

#include "gamescenelevel.h"
#include "types.h"
#include "core.h"
#include "graphicsscene.h"
#include "graphicscamera.h"
#include "physicsscene.h"
#include "audiocontroller.h"
#include "gamecontroller.h"
#include "gameobjectguibutton.h"
#include "gameobjectplayer.h"
#include "gamescenegameover.h"
#include "gamescenepause.h"
#include "gamelevelloader.h"

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
	float tilt = pGameController->tiltState().x;
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
	GameLevelLoader loader(this);
	return loader.load(levelId);
}

void GameSceneLevel::unload()
{
	GameLevelLoader loader(this);
	loader.unload();
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
