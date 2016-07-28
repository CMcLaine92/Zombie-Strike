#pragma once
#include "..\SGD Wrappers\SGD_Message.h"

class Spawner;

class CreateFatZombieMsg : public SGD::Message
{
	Spawner* m_pOwner = nullptr;

public:
	CreateFatZombieMsg(Spawner* owner);
	virtual ~CreateFatZombieMsg();
	Spawner* GetOwner(void) const { return m_pOwner; }
};

