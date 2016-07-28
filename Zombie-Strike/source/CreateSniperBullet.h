#pragma once
#include "..\SGD Wrappers\SGD_Message.h"


class Weapon;

class CreateSniperBullet : public SGD::Message
{
public:

	CreateSniperBullet(Weapon*);
	virtual ~CreateSniperBullet();

	Weapon* GetOwner(void) const { return m_pOwner; }

private:
	Weapon* m_pOwner = nullptr;

};

