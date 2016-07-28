#pragma once
#include "..\SGD Wrappers\SGD_Message.h"

class MovingObject;

class CreateTurretMessage : public SGD::Message
{
	MovingObject* m_pOwner = nullptr;

public:
	CreateTurretMessage(MovingObject* owner);
	virtual ~CreateTurretMessage();

	MovingObject* GetOwner ( void ) const { return m_pOwner; }

};

