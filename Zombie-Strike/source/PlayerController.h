#pragma once
#include "BaseBehavior.h"
class PlayerController :
	public BaseBehavior
{
public:
	enum Type { PISTOL, SHOTGUN, SMG, ASSUALT_RIFLE, SPECIAL, NONE };

	PlayerController();
	~PlayerController();

	bool Update(float dt, MovingObject* toUpdate, SGD::Point = { 0, 0 });


};

