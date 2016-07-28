#pragma once
#include "Weapon.h"
class PukerBlaster : public Weapon
{
	SGD::Point pos;
public:
	PukerBlaster(MovingObject* owner = nullptr);
	virtual ~PukerBlaster();
	virtual void Fire(float dt) override;
};

