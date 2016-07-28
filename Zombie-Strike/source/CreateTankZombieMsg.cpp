#include "CreateTankZombieMsg.h"
#include "Spawner.h"
#include "MessageID.h"


CreateTankZombieMsg::CreateTankZombieMsg(Spawner* owner) : Message(MessageID::MSG_CREATE_TANK_ZOMBIE)
{
	m_pOwner = owner;

}


CreateTankZombieMsg::~CreateTankZombieMsg()
{

	m_pOwner = nullptr;
}