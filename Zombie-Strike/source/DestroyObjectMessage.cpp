

#include "DestroyObjectMessage.h"
#include "MessageID.h"
#include "BaseObject.h"
#include <cassert>



DestroyObjectMessage::DestroyObjectMessage(BaseObject* ptr) : Message(MessageID::MSG_DESTROY_OBJECT)
{
	// Validate the parameter
	assert(ptr != nullptr
		&& "DestroyEntityMessage - cannot destroy null");

	// Store the parameter
	m_pObject = ptr;
	m_pObject->AddRef();
}

DestroyObjectMessage::~DestroyObjectMessage()
{
	m_pObject->Release();
	m_pObject = nullptr;
}
