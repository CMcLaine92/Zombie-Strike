#include "CreateARifleBullet.h"
#include "MessageID.h"
#include "Weapon.h"

CreateARifleBullet::CreateARifleBullet(Weapon* owner) : Message(MessageID::MSG_CREATE_ASSRFLE_BLT)
{
	m_pOwner = owner;
	
}


CreateARifleBullet::~CreateARifleBullet()
{
	
	m_pOwner = nullptr;
}
