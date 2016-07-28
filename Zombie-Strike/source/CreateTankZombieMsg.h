#pragma once
#include "..\SGD Wrappers\SGD_Message.h"

class Spawner;


class CreateTankZombieMsg : public SGD::Message
{
	Spawner* m_pOwner = nullptr;

public:
	CreateTankZombieMsg(Spawner* owner);
	virtual ~CreateTankZombieMsg();
	Spawner* GetOwner(void) const { return m_pOwner; }
};

