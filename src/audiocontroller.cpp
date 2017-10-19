#include <array>

#include <QSoundEffect>

#include "glm/geometric.hpp"
#include "audiocontroller.h"

void AudioController::setListenerPosition(const glm::vec2& value)
{
	m_listenerPos = value;
}

void AudioController::playSound(SoundId soundId, const glm::vec2& soundPos)
{
	auto pSound = new QSoundEffect;
	pSound->setSource(QUrl::fromLocalFile(QString::fromStdString(soundIdToFilename(soundId))));
	pSound->setVolume(soundVolume(soundId, soundPos));
	pSound->play();

	m_sounds.push_back(pSound);
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
		switch (sound->status()) {
			case QSoundEffect::Null:
			case QSoundEffect::Error: {
				stopedSounds.push_back(sound);
				break;
			}
			case QSoundEffect::Loading: {
				//
				break;
			}
			case QSoundEffect::Ready: {
				if (!sound->isPlaying()) {
					stopedSounds.push_back(sound);
				}
				break;
			}
			default:
				break;
		}
	}
	for (auto p: stopedSounds) {
		p->stop();
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
		":/res/snd.wav", //SoundId_0
	};

	return table[soundId];
}

glm::vec2 AudioController::soundRadiuses(SoundId soundId)
{
	static const std::array<glm::vec2, SoundId_Count> table = {
		glm::vec2(2.0f, 3.0f), //SoundId_0
	};

	return table[soundId];
}
