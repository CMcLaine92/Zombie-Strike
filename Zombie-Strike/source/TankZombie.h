#pragma once
#include "Zombie.h"
class TankZombie : public Zombie
{
public:
	TankZombie();
	virtual ~TankZombie();

	
	virtual int GetType(void) const override { return OBJ_TANK_ZOMBIE; }
	virtual void HandleEvent(const SGD::Event* pEvent) override;

};

