#pragma once
#include "Bullet.h"
class Grenade : public Bullet
{
	float speed = 0.0f;
public:
	Grenade();
	virtual ~Grenade();
	virtual void Update(float dt);

	
};

