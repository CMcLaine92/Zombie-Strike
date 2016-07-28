#include "PatrolBehavior.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "MovingObject.h"

PatrolBehavior::PatrolBehavior()
{
}


PatrolBehavior::~PatrolBehavior()
{
}

/*virtual*/ bool PatrolBehavior::Update(float dt, MovingObject* toUpdate, SGD::Point wayPoint)
{
	// Vector from Object to its Waypoint
	SGD::Vector toWaypoint = wayPoint - toUpdate->GetPosition();

	if (toWaypoint.ComputeLength() < 32)
	{
		return true;
	}
	else
	{
		toWaypoint.Normalize();
		if (toWaypoint.ComputeDotProduct(toUpdate->GetDirection()) < 0.999f)
		{
			if (toUpdate->GetDirection().ComputeSteering(toWaypoint) > 0)
				toUpdate->SetRotation(toUpdate->GetRotation() + (SGD::PI * 2  * dt)); //Turn left


			else if (toUpdate->GetDirection().ComputeSteering(toWaypoint) < 0)
				toUpdate->SetRotation(toUpdate->GetRotation() - (SGD::PI * 2  * dt)); //Turn right

			SGD::Vector orientation = { 0, -1 };
			orientation.Rotate(toUpdate->GetRotation());
			toUpdate->SetDirection(orientation);

			SGD::Vector newVelocity = orientation * toUpdate->GetMoveSpeed();

			toUpdate->SetVelocity(newVelocity);

		}
		return false;

	}
	

}
