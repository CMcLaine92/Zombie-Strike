#pragma once
#include "BaseBehavior.h"
class PatrolBehavior : public BaseBehavior
{
public:
	PatrolBehavior();
	~PatrolBehavior();

	bool Update(float dt, MovingObject* toUpdate, SGD::Point = { 0, 0 });


};

