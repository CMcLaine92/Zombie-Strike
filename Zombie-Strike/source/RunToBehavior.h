#pragma once
#include "BaseBehavior.h"
class RunToBehavior : public BaseBehavior
{
public:
	RunToBehavior();
	~RunToBehavior();

	bool Update(float dt, MovingObject* toUpdate, SGD::Point = { 0, 0 });

};

