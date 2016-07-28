#pragma once
#include "BaseBehavior.h"
#include "../SGD Wrappers/SGD_Geometry.h"
class RotateTowardsBehavior : public BaseBehavior
{
public:
	RotateTowardsBehavior();
	~RotateTowardsBehavior();

	bool Update(float dt, MovingObject* toUpdate, SGD::Point = { 0, 0 });

	


};

