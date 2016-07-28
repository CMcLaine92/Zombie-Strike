#include "CreatePukeBullet.h"
#include "MessageID.h"

#include "Weapon.h"


CreatePukeBullet::CreatePukeBullet(Weapon* owner) : Message(MessageID::MSG_CREATE_PUKE)
{
	m_pOwner = owner;
}


CreatePukeBullet::~CreatePukeBullet()
{
	m_pOwner = nullptr;
}
