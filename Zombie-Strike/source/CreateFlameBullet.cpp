#include "CreateFlameBullet.h"
#include "MessageID.h"
#include "Weapon.h"


CreateFlameBullet::CreateFlameBullet(Weapon* owner) : Message(MessageID::MSG_CREATE_FLAME)
{
	m_pOwner = owner;
}


CreateFlameBullet::~CreateFlameBullet()
{
	m_pOwner = nullptr;
}
