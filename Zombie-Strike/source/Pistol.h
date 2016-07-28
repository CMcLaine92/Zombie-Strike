#pragma once
#include "Weapon.h"
class Pistol : public Weapon
{
public:
	Pistol(MovingObject* owner = nullptr);
	virtual ~Pistol();
	virtual void Fire(float dt) override;
};

