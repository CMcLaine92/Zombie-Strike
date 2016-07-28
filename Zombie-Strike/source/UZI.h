#pragma once
#include "Weapon.h"
class UZI : public Weapon
{
public:
	UZI(MovingObject* owner);
	virtual ~UZI() = default;
	virtual void Fire(float dt) override;


};

