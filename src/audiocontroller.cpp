#include <array>

#include <QSoundEffect>

#include "glm/geometric.hpp"
#include "audiocontroller.h"

struct SoundData {
	QSoundEffect soundEffect;
	const Transform *pTransform;
	SoundId id;
	bool isInit;
	bool isLoop;

	SoundData(SoundId _id, const Transform *p, bool loop) :
		soundEffect(), pTransform(p), id(_id), isInit(false), isLoop(loop) {}
};

void AudioController::setListenerPosition(const glm::vec2& value)
{
	m_listenerPos = value;
}

void AudioController::playSound(SoundId soundId, const Transform* pTransform)
{
	m_sounds.push_back(new SoundData(soundId, pTransform, false));
}

void AudioController::playAmbient(SoundId soundId)
{
	m_sounds.push_back(new SoundData(soundId, nullptr, true));
}

bool AudioController::process(AbstractControllerMessage* pMessage)
{
	switch (pMessage->type()) {
	case CMT_ControllerInit: {
		auto pMsg = msg_cast<ControllerInitMessage>(pMessage);
		if (pMsg) {
			//
		}
		return true;
	}
	case CMT_ControllerUpdate: {
		auto pMsg = msg_cast<ControllerUpdateMessage>(pMessage);
		if (pMsg)
			update();
		return true;
	}
	default: break;
	}
	return false;
}

AudioController::AudioController() :
	m_sounds(),
	m_listenerPos()
{

}

AudioController::~AudioController()
{
	for (auto p: m_sounds) {
		p->soundEffect.stop();
		delete p;
	}
	m_sounds.clear();
}

void AudioController::update()
{
	SoundsList stopedSounds;
	for (auto sound: m_sounds) {
		if (sound->isInit == false) {
			sound->soundEffect.setSource(QUrl::fromLocalFile(QString::fromStdString(soundIdToFilename(sound->id))));
			if (sound->isLoop)
				sound->soundEffect.setLoopCount(QSoundEffect::Infinite);
			sound->soundEffect.play();
			sound->isInit = true;
		}

		sound->soundEffect.setVolume((sound->pTransform != nullptr) ?
										 soundVolume(sound->id, sound->pTransform->pos) :
										 0.9f);

		if (!sound->soundEffect.isPlaying())
			stopedSounds.push_back(sound);
	}
	for (auto p: stopedSounds) {
		p->soundEffect.stop();
		m_sounds.remove(p);
		delete p;
	}
}

float AudioController::soundVolume(SoundId soundId, const glm::vec2& soundPos) const
{
	const float dist = glm::distance(m_listenerPos, soundPos);
	glm::vec2 radiuses = soundRadiuses(soundId);

	if (dist < radiuses[0])
		return 1.0f;
	else if (dist > radiuses[1])
		return 0.0f;
	else
		return (radiuses[1] - dist) / (radiuses[1] - radiuses[0]);
}

std::string AudioController::soundIdToFilename(SoundId soundId)
{
	static const std::array<std::string, SoundId_Count> table = {
		":/res/ambient1.wav", // SoundId_Ambient1
		":/res/jump.wav", // SoundId_Jump
		":/res/broken_jump.wav", // SoundId_BrokenJump
		":/res/shot.wav", // SoundId_Shot
		":/res/pass.wav", // SoundId_LevelPassed
		":/res/game_over.wav", // SoundId_GameOver
	};

	return table[soundId];
}

glm::vec2 AudioController::soundRadiuses(SoundId soundId)
{
	static const std::array<glm::vec2, SoundId_Count> table = {
		glm::vec2(), // SoundId_Ambient1
		glm::vec2(2.0f, 5.0f), // SoundId_Jump
		glm::vec2(2.0f, 5.0f), // SoundId_BrokenJump
		glm::vec2(3.0f, 8.0f), // SoundId_Shot
		glm::vec2(), // SoundId_LevelPassed
		glm::vec2(), // SoundId_GameOver
	};

	return table[soundId];
}
