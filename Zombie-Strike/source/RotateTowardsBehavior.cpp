#include "RotateTowardsBehavior.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "MovingObject.h"


RotateTowardsBehavior::RotateTowardsBehavior()
{

}


RotateTowardsBehavior::~RotateTowardsBehavior()
{
}

/*virtual*/ bool RotateTowardsBehavior::Update(float dt, MovingObject* toUpdate, SGD::Point wayPoint)
{


	// Vector from Object to its Waypoint
	SGD::Vector toWaypoint = wayPoint - toUpdate->GetPosition();

	toWaypoint.Normalize();
	if (toWaypoint.ComputeDotProduct(toUpdate->GetDirection()) < 0.999f)
	{
		if (toUpdate->GetDirection().ComputeSteering(toWaypoint) > 0)
			toUpdate->SetRotation(toUpdate->GetRotation() + (SGD::PI * 0.15f * dt)); //Turn left
		

		else if (toUpdate->GetDirection().ComputeSteering(toWaypoint) < 0)
			toUpdate->SetRotation(toUpdate->GetRotation() - (SGD::PI * 0.15f * dt)); //Turn right

		SGD::Vector orientation = { 0, -1 };
		orientation.Rotate(toUpdate->GetRotation());
		toUpdate->SetDirection(orientation);
		return false;
	}

	return true;

}
