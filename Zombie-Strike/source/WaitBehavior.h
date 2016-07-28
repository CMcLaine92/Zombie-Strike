#pragma once
#include "BaseBehavior.h"
class WaitBehavior : public BaseBehavior
{
public:
	WaitBehavior();
	~WaitBehavior();

	bool Update(float dt, MovingObject* toUpdate, SGD::Point = { 0, 0 });



};

