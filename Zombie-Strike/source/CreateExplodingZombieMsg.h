#pragma once
#include "..\SGD Wrappers\SGD_Message.h"

class Spawner;


class CreateExplodingZombieMsg : public SGD::Message
{
public:
	Spawner* m_pOwner = nullptr;

public:
	CreateExplodingZombieMsg(Spawner* owner);
	virtual ~CreateExplodingZombieMsg();
	Spawner* GetOwner(void) const { return m_pOwner; }
};

