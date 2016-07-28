#include "WaitBehavior.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "MovingObject.h"

WaitBehavior::WaitBehavior()
{
}


WaitBehavior::~WaitBehavior()
{
}

/*virtual*/ bool WaitBehavior::Update(float dt, MovingObject* toUpdate, SGD::Point wayPoint) /*override*/
{
	toUpdate->SetVelocity({ 0, 0 });
	return false;
}