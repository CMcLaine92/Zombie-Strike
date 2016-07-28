#include "AlertBehavior.h"
#include "MovingObject.h"

AlertBehavior::AlertBehavior()
{
}


AlertBehavior::~AlertBehavior()
{
}

/*virtual*/ bool AlertBehavior::Update(float dt, MovingObject* toUpdate, SGD::Point wayPoint)
{
	// Vector from Object to its Waypoint
	SGD::Vector toWaypoint = wayPoint - toUpdate->GetPosition();

	if (toWaypoint.ComputeLength() < 32)
	{
		return true;
	}
	else
	{
		if (toWaypoint.ComputeLength() < 400.0f)
		{
			if (toUpdate->UpdateAttackTime(dt))
				toUpdate->Attack();
		}
		toWaypoint.Normalize();
		if (toWaypoint.ComputeDotProduct(toUpdate->GetDirection()) < 0.999f)
		{
			if (toUpdate->GetDirection().ComputeSteering(toWaypoint) > 0)
				toUpdate->SetRotation(toUpdate->GetRotation() + (SGD::PI  * dt)); //Turn left
			else if (toUpdate->GetDirection().ComputeSteering(toWaypoint) < 0)
				toUpdate->SetRotation(toUpdate->GetRotation() - (SGD::PI * dt)); //Turn right

			SGD::Vector orientation = { 0, -1 };
			orientation.Rotate(toUpdate->GetRotation());
			toUpdate->SetDirection(orientation);

			SGD::Vector newVelocity = orientation * toUpdate->GetMoveSpeed() * 1.75f;

			toUpdate->SetVelocity(newVelocity);
		}
		return false;
	}




}

