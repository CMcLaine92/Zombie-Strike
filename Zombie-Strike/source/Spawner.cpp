#include "Spawner.h"
#include "CreateZombieMessage.h"
#include "CreateExplodingZombieMsg.h"
#include "CreateFastZombieMsg.h"
#include "CreateFatZombieMsg.h"
#include "CreateTankZombieMsg.h"

Spawner::Spawner() 
{

}


Spawner::~Spawner()
{

}

void Spawner::SpawnEnemy(int type)
{

	switch (type)
	{
	case OBJ_SLOW_ZOMBIE:
	{
		CreateZombieMessage* pMsg = new CreateZombieMessage(this);
		pMsg->QueueMessage();
		pMsg = nullptr;
	}
		break;
	case OBJ_FAST_ZOMBIE:
	{
		CreateFastZombieMsg* pMsg = new CreateFastZombieMsg(this);
		pMsg->QueueMessage();
		pMsg = nullptr;
	}
		break;
	case OBJ_FAT_ZOMBIE:
	{
		CreateFatZombieMsg* pMsg = new CreateFatZombieMsg(this);
		pMsg->QueueMessage();
		pMsg = nullptr;
	}
		break;
	case OBJ_TANK_ZOMBIE:
	{
		CreateTankZombieMsg* pMsg = new CreateTankZombieMsg(this);
		pMsg->QueueMessage();
		pMsg = nullptr;
	}
		break;
	case OBJ_EXPLODING_ZOMBIE:
	{
		CreateExplodingZombieMsg* pMsg = new CreateExplodingZombieMsg(this);
		pMsg->QueueMessage();
		pMsg = nullptr;
	}
		break;
	}
	
				
		
		
}
	










