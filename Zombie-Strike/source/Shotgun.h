#pragma once
#include "Weapon.h"
class Shotgun : public Weapon
{
public:
	Shotgun(MovingObject* owner = nullptr);
	virtual ~Shotgun();
	virtual void Fire(float dt) override;

};

