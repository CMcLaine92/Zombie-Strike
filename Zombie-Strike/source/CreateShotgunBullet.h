#pragma once
#include "..\SGD Wrappers\SGD_Message.h"

class Weapon;

class CreateShotgunBullet : public SGD::Message
{
public:
	CreateShotgunBullet(Weapon*);
	virtual ~CreateShotgunBullet();

	Weapon* GetOwner(void) const { return m_pOwner; }

private:
	Weapon* m_pOwner = nullptr;
};

