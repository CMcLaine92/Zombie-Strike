#include "CreateZombieMessage.h"
#include "Spawner.h"
#include "MessageID.h"


CreateZombieMessage::CreateZombieMessage(Spawner* owner) : Message(MessageID::MSG_CREATE_SLOW_ZOMBIE)
{
	m_pOwner = owner;

}


CreateZombieMessage::~CreateZombieMessage()
{

	m_pOwner = nullptr;
}
