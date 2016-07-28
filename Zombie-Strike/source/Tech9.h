#pragma once
#include "Weapon.h"
class Tech9 : public Weapon
{
public:
	Tech9(MovingObject* owner = nullptr);
	virtual ~Tech9();
	virtual void Fire(float dt) override;
};

