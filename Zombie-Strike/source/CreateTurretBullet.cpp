#include "CreateTurretBullet.h"
#include "Turret.h"
#include "MessageID.h"
#include <cassert>


CreateTurretBullet::CreateTurretBullet(Turret * owner) : Message(MessageID::MSG_CREATE_TURRET_BLT)
{
	m_pOwner = owner;
	m_pOwner->AddRef();
}


CreateTurretBullet::~CreateTurretBullet()
{
	m_pOwner->Release();
	m_pOwner = nullptr;
}
