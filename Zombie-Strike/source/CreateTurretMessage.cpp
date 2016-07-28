#include "CreateTurretMessage.h"
#include "MovingObject.h"
#include "MessageID.h"
#include <cassert>


CreateTurretMessage::CreateTurretMessage(MovingObject* owner) : Message(MessageID::MSG_CREATE_TURRET)
{
	m_pOwner = owner;
	m_pOwner->AddRef();
}


CreateTurretMessage::~CreateTurretMessage()
{
	m_pOwner->Release();
	m_pOwner = nullptr;
}
