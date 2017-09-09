#include "abstractcontroller.h"

AbstractController::AbstractController() :
	m_messages()
{
}

AbstractController::~AbstractController()
{
}

void AbstractController::sendMessage(AbstractControllerMessage* pMessage, MessagePriority priority)
{
	switch (priority) {
	case MessagePriority_Normal: {
		m_messages.push_back(pMessage);
		break;
	}
	case MessagePriority_High: {
		process(pMessage);
		delete pMessage;
		break;
	}
	}
}

void AbstractController::readMessages()
{
	while (!m_messages.empty()) {
		AbstractControllerMessage *pMsg = m_messages.front();
		m_messages.pop_front();
		process(pMsg);
		delete pMsg;
	}
}

AbstractControllerMessage::AbstractControllerMessage(ControllerMessageType t) :
	m_type(t)
{
}

ControllerMessageType AbstractControllerMessage::type() const
{
	return m_type;
}

ControllerMessageType AbstractControllerMessage::typeOfClass()
{
	return CMT_None;
}
