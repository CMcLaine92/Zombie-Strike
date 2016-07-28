#pragma once
#include "..\SGD Wrappers\SGD_Message.h"
#include "../SGD Wrappers/SGD_Geometry.h"

class CreateBloodMsg : public SGD::Message
{
	SGD::Point spawnPos = { 0.0f, 0.0f };

public:
	CreateBloodMsg(SGD::Point);
	virtual ~CreateBloodMsg();

	SGD::Point GetSpawnPos(void) const { return spawnPos; }


};

