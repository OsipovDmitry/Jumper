#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <string>
#include <list>

#include "abstractcontroller.h"

class QSoundEffect;

class AudioController : public AbstractController
{
public:
	static ControllerType controllerType() { return ControllerType_Audio; }

	void setListenerPosition(const glm::vec2& value);

	void playSound(SoundId soundId, const glm::vec2& soundPos);

protected:
	virtual bool process(AbstractControllerMessage *pMessage);

private:
	using SoundsList = std::list<QSoundEffect*>;

	AudioController();
	~AudioController();

	void update();

	float soundVolume(SoundId soundId, const glm::vec2& soundPos) const;

	static std::string soundIdToFilename(SoundId soundId);
	static glm::vec2 soundRadiuses(SoundId soundId);

	SoundsList m_sounds;
	glm::vec2 m_listenerPos;

	friend class Core;
};

#endif // AUDIOCONTROLLER_H
