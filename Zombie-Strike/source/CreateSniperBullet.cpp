#include "CreateSniperBullet.h"
#include "MessageID.h"
#include "Weapon.h"

CreateSniperBullet::CreateSniperBullet(Weapon* owner) : Message(MessageID::MSG_CREATE_SNPR_BLT)
{
	m_pOwner = owner;
	
}


CreateSniperBullet::~CreateSniperBullet()
{
	
	m_pOwner = nullptr;
}
