#pragma once
#include "Weapon.h"
class GrenadeLauncher : public Weapon
{
public:
	GrenadeLauncher(MovingObject* owner);
	virtual ~GrenadeLauncher();
	virtual void Fire(float dt) override;

};

