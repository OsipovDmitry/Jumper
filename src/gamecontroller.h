#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <array>
#include <bitset>

#include "abstractcontroller.h"
#include "gameabstractscene.h"

class PhysicsGeometry;
class GameObject;

class GameController : public AbstractController
{
public:
	static ControllerType controllerType() { return ControllerType_Game; }

	bool keyState(KeyCode keyCode) const;
	glm::vec2 tiltState() const;

protected:
	virtual bool process(AbstractControllerMessage *pMessage);

private:
	GameController();
	~GameController();

	void init();
	void update(uint32_t dt);
	void mouseClick(int32_t x, int32_t y);
	void tilt(float x, float y);
	void keyPress(KeyCode code);
	void keyRelease(KeyCode code);

	void changeLevel(GameSceneId id, GameAbstractScene::AbstractActivateData *pActivateData);

	std::array<GameAbstractScene*, GameSceneId_Count> m_scenes;
	GameSceneId m_currentSceneId;
	std::bitset<KeyCode_Count> m_keys;
	glm::vec2 m_tilt;

	friend class Core;
};

class GameMouseClickMessage : public AbstractControllerMessage {
public:
	GameMouseClickMessage(int32_t xVal, int32_t yVal) : AbstractControllerMessage(CMT_GameMouseClick), x(xVal), y(yVal) {}
	static ControllerMessageType typeOfClass() { return CMT_GameMouseClick; }

	int32_t x, y;
};

class GameTiltMessage : public AbstractControllerMessage {
public:
	GameTiltMessage(float xVal, float yVal) : AbstractControllerMessage(CMT_GameTilt), x(xVal), y(yVal) {}
	static ControllerMessageType typeOfClass() { return CMT_GameTilt; }

	float x, y;
};

class GameKeyPressMessage : public AbstractControllerMessage {
public:
	GameKeyPressMessage(KeyCode code) : AbstractControllerMessage(CMT_GameKeyPress), keyCode(code) {}
	static ControllerMessageType typeOfClass() { return CMT_GameKeyPress; }

	KeyCode keyCode;
};

class GameKeyReleaseMessage : public AbstractControllerMessage {
public:
	GameKeyReleaseMessage(KeyCode code) : AbstractControllerMessage(CMT_GameKeyRelease), keyCode(code) {}
	static ControllerMessageType typeOfClass() { return CMT_GameKeyRelease; }

	KeyCode keyCode;
};

class GameObjectUseMessage : public AbstractControllerMessage {
public:
	GameObjectUseMessage(GameObject *pObject, GameObject *pOtherObject) : AbstractControllerMessage(CMT_GameObjectUse), pGameObject(pObject), pOtherGameObject(pOtherObject) {}
	static ControllerMessageType typeOfClass() { return CMT_GameObjectUse; }

	GameObject *pGameObject, *pOtherGameObject;
};

class GameChangeSceneMessage : public AbstractControllerMessage {
public:
	GameChangeSceneMessage(GameSceneId id, GameAbstractScene::AbstractActivateData *pData = nullptr) :
		AbstractControllerMessage(CMT_GameChangeScene),
		sceneId(id),
		pActivateData(pData) {}
	static ControllerMessageType typeOfClass() { return CMT_GameChangeScene; }

	GameSceneId sceneId;
	GameAbstractScene::AbstractActivateData *pActivateData;
};

class GameLoadLevelMessage : public AbstractControllerMessage {
public:
	GameLoadLevelMessage(GameLevelId id) : AbstractControllerMessage(CMT_GameLoadLevel), levelId(id) {}
	static ControllerMessageType typeOfClass() { return CMT_GameLoadLevel; }

	GameLevelId levelId;
};

#endif // GAMECONTROLLER_H
