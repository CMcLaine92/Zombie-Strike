#pragma once
#include "Zombie.h"
class ExplodingZombie :	public Zombie
{
public:
	ExplodingZombie();
	virtual ~ExplodingZombie();
	virtual void Update(float);

	virtual int GetType(void) const override { return OBJ_EXPLODING_ZOMBIE; }
	virtual void HandleEvent(const SGD::Event* pEvent) override;

	virtual void HandleCollision(const IBase* pOther) override;

};

