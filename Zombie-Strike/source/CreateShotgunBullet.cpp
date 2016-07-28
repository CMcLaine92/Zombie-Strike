#include "CreateShotgunBullet.h"
#include "MessageID.h"

#include "Weapon.h"

CreateShotgunBullet::CreateShotgunBullet(Weapon* owner) : Message(MessageID::MSG_CREATE_SHTGN_BLT)
{
	m_pOwner = owner;
	
}


CreateShotgunBullet::~CreateShotgunBullet()
{
	m_pOwner = nullptr;
	
}
