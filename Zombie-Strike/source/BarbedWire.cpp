#include "BarbedWire.h"
#include "../SGD Wrappers/SGD_Event.h"

BarbedWire::BarbedWire()
{
	this->SetType(ObjectType::OBJ_BARBEDWIRE);
	this->SetAnimation("barbedwire");

	m_fCurrHP = m_fMaxHP = 100.0f;

	m_fDamage = 10.0f;

	RegisterForEvent("REPAIR_BARBEDWIRE");
	RegisterForEvent("UPGRADE_BARBEDWIRE_HEALTH");
	RegisterForEvent("UPGRADE_BARBEDWIRE_DAMAGE");

}

BarbedWire::~BarbedWire()
{
}

void BarbedWire::Update( float dt )
{

	SandBag::Update(dt);
}

void BarbedWire::Render( void )
{

	SandBag::Render();
}

void BarbedWire::HandleCollision( const IBase* pOther )
{
	if (this->isActive == false)
		return;


	// zombie collision
	if (pOther->GetType() == ObjectType::OBJ_SLOW_ZOMBIE || 
		pOther->GetType() == ObjectType::OBJ_FAST_ZOMBIE || 
		pOther->GetType() == ObjectType::OBJ_FAT_ZOMBIE )
	{
		// lower zombie HP by damage
		SGD::Event* msg = new SGD::Event("BARBWIRE");
		msg->QueueEvent(pOther);
		msg = nullptr;
		SandBag::HandleCollision(pOther);

	}


	// Let the SandBag handle damage to "this"
}

void BarbedWire::HandleEvent(const SGD::Event* pEvent)
{
	if (pEvent->GetEventID() == "REPAIR_BARBEDWIRE")
	{
		isActive = true;
		m_fCurrHP = m_fMaxHP;

	}
	if (pEvent->GetEventID() == "UPGRADE_BARBEDWIRE_HEALTH")
	{
		m_fMaxHP += 50;
		m_fCurrHP = m_fMaxHP;
	}
	if (pEvent->GetEventID() == "UPGRADE_BARBEDWIRE_DAMAGE")
	{
		m_fDamage += 5.0f;
	}
}
