#include "CreateGrenadeBullet.h"
#include "MessageID.h"
#include "Weapon.h"


CreateGrenadeBullet::CreateGrenadeBullet(Weapon* owner) : Message(MessageID::MSG_CREATE_NADE)
{
	m_pOwner = owner;
}


CreateGrenadeBullet::~CreateGrenadeBullet()
{
	m_pOwner = nullptr;
}
