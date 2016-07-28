#include "CreateFatZombieMsg.h"
#include "Spawner.h"
#include "MessageID.h"


CreateFatZombieMsg::CreateFatZombieMsg(Spawner* owner) : Message(MessageID::MSG_CREATE_FAT_ZOMBIE)
{
	m_pOwner = owner;

}


CreateFatZombieMsg::~CreateFatZombieMsg()
{

	m_pOwner = nullptr;
}