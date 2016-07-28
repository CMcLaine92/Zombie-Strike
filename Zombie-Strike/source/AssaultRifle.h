#pragma once
#include "Weapon.h"
class AssaultRifle : public Weapon
{
public:
	AssaultRifle(MovingObject* owner = nullptr);
	virtual ~AssaultRifle();
	virtual void Fire(float dt) override;
};

