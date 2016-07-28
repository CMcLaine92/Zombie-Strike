#pragma once
#include "Weapon.h"
class Ak47 : public Weapon
{
public:
	Ak47(MovingObject* owner);
	virtual ~Ak47();
	virtual void Fire(float dt) override;

};

