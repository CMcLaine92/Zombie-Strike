#pragma once
#include "BaseBehavior.h"
class AlertBehavior : public BaseBehavior
{
public:
	AlertBehavior();
	~AlertBehavior();

	bool Update(float dt, MovingObject* toUpdate, SGD::Point = { 0, 0 });
	

};

