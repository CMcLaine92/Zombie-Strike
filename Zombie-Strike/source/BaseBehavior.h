#pragma once
#include "../SGD Wrappers/SGD_Geometry.h"



class MovingObject;

class BaseBehavior
{
public:
	
	BaseBehavior() = default;
	virtual ~BaseBehavior() = default;

	virtual bool Update(float dt, MovingObject* toUpdate, SGD::Point) = 0;

	
};

