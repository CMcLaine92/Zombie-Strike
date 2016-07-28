#pragma once
#include "Weapon.h"
class AutoShotgun : public Weapon
{
public:
	AutoShotgun(MovingObject* owner = nullptr);
	virtual ~AutoShotgun();
	virtual void Fire(float dt) override;

};

