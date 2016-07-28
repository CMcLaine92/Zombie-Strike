#pragma once
#include "..\SGD Wrappers\SGD_Message.h"

class Weapon;

class CreateGrenadeBullet : public SGD::Message
{
public:
	CreateGrenadeBullet(Weapon*);
	virtual ~CreateGrenadeBullet();

	Weapon* GetOwner(void) const { return m_pOwner; }

private:
	Weapon* m_pOwner = nullptr;
};

