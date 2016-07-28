#pragma once
#include "..\SGD Wrappers\SGD_Message.h"

class Spawner;
class CreateZombieMessage : public SGD::Message
{
	Spawner* m_pOwner = nullptr;
	
public:
	CreateZombieMessage(Spawner* owner);
	virtual ~CreateZombieMessage(); 
	Spawner* GetOwner(void) const { return m_pOwner; }

};

