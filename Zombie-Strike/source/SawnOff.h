#pragma once
#include "Weapon.h"
class SawnOff :public Weapon
{
public:
	SawnOff(MovingObject* owner = nullptr);
	virtual ~SawnOff();
	virtual void Fire(float dt) override;
};

