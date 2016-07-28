#pragma once
#include "Weapon.h"
class P90 : public Weapon
{
public:
	P90(MovingObject* owner = nullptr);
	virtual ~P90();
	virtual void Fire(float dt) override;
};

