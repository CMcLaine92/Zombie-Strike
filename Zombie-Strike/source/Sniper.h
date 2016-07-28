#pragma once
#include "Weapon.h"
class Sniper : public Weapon
{
public:
	Sniper(MovingObject* owner = nullptr);
	virtual ~Sniper();
	virtual void Fire(float dt) override;
};

