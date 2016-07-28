#include "CreateFastZombieMsg.h"
#include "Spawner.h"
#include "MessageID.h"


CreateFastZombieMsg::CreateFastZombieMsg(Spawner* owner) : Message(MessageID::MSG_CREATE_FAST_ZOMBIE)
{
	m_pOwner = owner;

}


CreateFastZombieMsg::~CreateFastZombieMsg()
{

	m_pOwner = nullptr;
}