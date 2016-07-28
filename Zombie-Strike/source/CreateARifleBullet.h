#pragma once
#include "..\SGD Wrappers\SGD_Message.h"
class Weapon;


class CreateARifleBullet : public SGD::Message
{
public:
	CreateARifleBullet(Weapon*);
	virtual ~CreateARifleBullet();

	Weapon* GetOwner(void) const { return m_pOwner; }

private:
	Weapon* m_pOwner = nullptr;
};

