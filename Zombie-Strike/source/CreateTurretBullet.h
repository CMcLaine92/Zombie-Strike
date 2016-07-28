#pragma once
#include "..\SGD Wrappers\SGD_Message.h"

class Turret;

class CreateTurretBullet : public SGD::Message
{
	Turret * m_pOwner = nullptr;

public:
	CreateTurretBullet(Turret * owner);
	virtual ~CreateTurretBullet();

	Turret* GetOwner(void) const { return m_pOwner; }

};

