#include "RunToBehavior.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "MovingObject.h"

RunToBehavior::RunToBehavior()
{
}


RunToBehavior::~RunToBehavior()
{
}

/*virtual*/ bool RunToBehavior::Update(float dt, MovingObject* toUpdate, SGD::Point wayPoint) /*override*/
{
	// Vector from Object to its Waypoint
	SGD::Vector toWaypoint = wayPoint - toUpdate->GetPosition();
	float length = toWaypoint.ComputeLength();
	if (length < 45.0f)
	{
		return true;
	}
	else
	{
		toWaypoint.Normalize();
		if (toWaypoint.ComputeDotProduct(toUpdate->GetDirection()) < 0.999f)
		{
			if (toUpdate->GetDirection().ComputeSteering(toWaypoint) > 0)
				toUpdate->SetRotation(toUpdate->GetRotation() + (SGD::PI * 2 * dt)); //Turn left


			else if (toUpdate->GetDirection().ComputeSteering(toWaypoint) < 0)
				toUpdate->SetRotation(toUpdate->GetRotation() - (SGD::PI * 2 * dt)); //Turn right
		}

			SGD::Vector orientation = { 0, -1 };
			orientation.Rotate(toUpdate->GetRotation());
			toUpdate->SetDirection(orientation);

			SGD::Vector newVelocity = orientation * toUpdate->GetMoveSpeed() * 2.0f;

			toUpdate->SetVelocity(newVelocity);

		
		return false;

	}

}




