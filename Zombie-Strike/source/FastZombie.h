#pragma once
#include "Zombie.h"
class FastZombie : public Zombie
{
public:
	FastZombie();
	virtual ~FastZombie();

	

	virtual int GetType(void) const override { return OBJ_FAST_ZOMBIE; }
	virtual void HandleEvent(const SGD::Event* pEvent) override;


};

