#pragma once
#include "Zombie.h"
#include "PukerBlaster.h"


class FatZombie : public Zombie
{
public:
	FatZombie();
	virtual ~FatZombie();

	virtual void Update(float);

	virtual int GetType(void) const override { return OBJ_FAT_ZOMBIE; }
	virtual void HandleEvent(const SGD::Event* pEvent) override;

private:

	
	PukerBlaster pukeBlaster = PukerBlaster(this);

};

