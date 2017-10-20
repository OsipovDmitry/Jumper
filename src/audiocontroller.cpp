#include <array>

#include <QSoundEffect>

#include "glm/geometric.hpp"
#include "audiocontroller.h"

struct SoundData {
	QSoundEffect soundEffect;
	const Transform *pTransform;
	SoundId id;
	bool isInit;

	SoundData(SoundId _id, const Transform *p) : soundEffect(), pTransform(p), id(_id), isInit(false) {}
};

void AudioController::setListenerPosition(const glm::vec2& value)
{
	m_listenerPos = value;
}

void AudioController::playSound(SoundId soundId, const Transform* pTransform)
{
	m_sounds.push_back(new SoundData(soundId, pTransform));
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

}

void AudioController::update()
{
	SoundsList stopedSounds;
	for (auto sound: m_sounds) {
		if (sound->isInit == false) {
			sound->soundEffect.setSource(QUrl::fromLocalFile(QString::fromStdString(soundIdToFilename(sound->id))));
			sound->soundEffect.play();
			sound->isInit = true;
		}

		sound->soundEffect.setVolume(soundVolume(sound->id, sound->pTransform->pos));

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
		":/res/jump.wav", // SoundId_Jump
		":/res/broken_jump.wav", // SoundId_BrokenJump
		":/res/pass.wav", // SoundId_LevelPassed
		":/res/shot.wav", // SoundId_Shot
	};

	return table[soundId];
}

glm::vec2 AudioController::soundRadiuses(SoundId soundId)
{
	static const std::array<glm::vec2, SoundId_Count> table = {
		glm::vec2(2.0f, 5.0f), // SoundId_Jump
		glm::vec2(2.0f, 5.0f), // SoundId_BrokenJump
		glm::vec2(3.0f, 4.0f), // SoundId_LevelPassed
		glm::vec2(3.0f, 8.0f), // SoundId_Shot
	};

	return table[soundId];
}
