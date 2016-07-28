#pragma once
#include "Weapon.h"
class Revolver : public Weapon
{
public:
	Revolver(MovingObject* owner);
	virtual ~Revolver() = default;
	virtual void Fire(float dt) override;

};

