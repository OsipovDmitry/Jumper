#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include <deque>
#include <inttypes.h>

#include "types.h"

// Макрос для объявления простых сообщений(без данных)
#define DECLARE_SIMPLE_MESSAGE(CLASS_NAME, MSG_TYPE) \
	class CLASS_NAME : public AbstractControllerMessage { \
	public: \
		CLASS_NAME() : AbstractControllerMessage(MSG_TYPE) {} \
		static ControllerMessageType typeOfClass() { return MSG_TYPE; } \
	};

enum ControllerMessageType {
	CMT_None = 0,

	CMT_CoreExit,
	CMT_CoreInit,
	CMT_CoreMouseClick,
	CMT_CoreUpdate,

	CMT_ControllerUpdate,

	CMT_GameMouseClick,
	CMT_GameOver,
	CMT_GameObjectsCollision,
};

class AbstractControllerMessage {
public:
	AbstractControllerMessage(ControllerMessageType t = CMT_None);
	virtual ~AbstractControllerMessage() {}

	ControllerMessageType type() const;
	static ControllerMessageType typeOfClass();

protected:
	ControllerMessageType m_type;
};

template <class T>
inline T *msg_cast(AbstractControllerMessage* pMsg) {
	return (pMsg->type() == T::typeOfClass()) ? static_cast<T*>(pMsg) : nullptr;
}

class AbstractController
{
public:
	enum MessagePriority {
		MessagePriority_Normal,
		MessagePriority_High,
	};

	AbstractController();
	virtual ~AbstractController();

	void sendMessage(AbstractControllerMessage *pMessage, MessagePriority priority = MessagePriority_Normal);
	void readMessages();

protected:
	virtual bool process(AbstractControllerMessage*) { return true; }

protected:
	std::deque<AbstractControllerMessage*> m_messages;

};

class ControllerUpdateMessage : public AbstractControllerMessage {
public:
	ControllerUpdateMessage(uint64_t timeVal, uint32_t dtVal) : AbstractControllerMessage(CMT_ControllerUpdate), time(dtVal), dt(dtVal) {}
	static ControllerMessageType typeOfClass() { return CMT_ControllerUpdate; }

	uint64_t time;
	uint32_t dt;
};

#endif // ABSTRACTCONTROLLER_H
