#include "CreatePistolBullet.h"
#include "MessageID.h"
#include "Weapon.h"

CreatePistolBullet::CreatePistolBullet(Weapon* owner) : Message(MessageID::MSG_CREATE_PSTL_BLT)
{
	m_pOwner = owner;


}


CreatePistolBullet::~CreatePistolBullet()
{
	
	m_pOwner = nullptr;
}
