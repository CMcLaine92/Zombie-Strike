#pragma once
#include "..\SGD Wrappers\SGD_Message.h"

class Weapon;

class CreatePukeBullet : public SGD::Message
{

public:
	CreatePukeBullet(Weapon*);
	virtual ~CreatePukeBullet();

	Weapon* GetOwner(void) const { return m_pOwner; }

private:
	Weapon* m_pOwner = nullptr;
};

