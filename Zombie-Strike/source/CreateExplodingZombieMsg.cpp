#include "CreateExplodingZombieMsg.h"
#include "Spawner.h"
#include "MessageID.h"


CreateExplodingZombieMsg::CreateExplodingZombieMsg(Spawner* owner) : Message(MessageID::MSG_CREATE_EXPLODING_ZOMBIE)
{
	m_pOwner = owner;

}


CreateExplodingZombieMsg::~CreateExplodingZombieMsg()
{

	m_pOwner = nullptr;
}