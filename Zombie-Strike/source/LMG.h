#pragma once
#include "Weapon.h"
class LMG :
	public Weapon
{
public:
	LMG(MovingObject* owner);
	virtual ~LMG();
	virtual void Fire(float dt) override;

};

