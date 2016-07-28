#pragma once
#include "Weapon.h"
#include "../SGD Wrappers/SGD_Listener.h"


class FlameThrower : public Weapon, SGD::Listener
{
public:
	FlameThrower(MovingObject* owner = nullptr);
	virtual ~FlameThrower();
	virtual void Fire(float dt) override;

};

