#pragma once
#include "..\SGD Wrappers\SGD_Message.h"

class Spawner;

class CreateFastZombieMsg : public SGD::Message
{
	Spawner* m_pOwner = nullptr;

public:
	CreateFastZombieMsg(Spawner* owner);
	virtual ~CreateFastZombieMsg();
	Spawner* GetOwner(void) const { return m_pOwner; }
};

