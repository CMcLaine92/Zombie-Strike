#include "SandBag.h"
#include "Game.h"
#include "../SGD Wrappers/SGD_Event.h"

SandBag::SandBag()
{
	this->SetType(ObjectType::OBJ_SANDBAG);
	this->SetAnimation("sandbag");

	m_fCurrHP = m_fMaxHP = 250.0f;
	RegisterForEvent("REPAIR_SANDBAGS");
}

SandBag::~SandBag()
{
	UnregisterFromEvent("REPAIR_SANDBAGS");
	UnregisterFromEvent("UPGRADE_SANDBAG_HEALTH");

}

void SandBag::Update( float dt )
{
	if (this->isActive == false)
		return;


	BaseObject::Update(dt);
}

void SandBag::Render( void )
{
	if (this->isActive == false)
		return;



	BaseObject::Render();
}

void SandBag::HandleCollision( const IBase* pOther )
{
	if (this->isActive == false)
		return;


	// zombie collision
	if (pOther->GetType() == ObjectType::OBJ_SLOW_ZOMBIE ||
		pOther->GetType() == ObjectType::OBJ_FAT_ZOMBIE ||
		pOther->GetType() == ObjectType::OBJ_FAST_ZOMBIE || 
		pOther->GetType() == ObjectType::OBJ_TANK_ZOMBIE )
	{
		// lower HP by zombie damage
		m_fCurrHP -= 10.0f * Game::GetInstance()->DeltaTime();


		// dead
		if (m_fCurrHP <= 0.0f)
		{
			// reset HP
			m_fCurrHP = 0;

			// deactivate
			this->isActive = false;
		}
	}
	if (pOther->GetType() == ObjectType::OBJ_EXPLODING_ZOMBIE)
	{
		m_fCurrHP -= 200.0f * Game::GetInstance()->DeltaTime();


		// dead
		if (m_fCurrHP <= 0.0f)
		{
			// reset HP
			m_fCurrHP = 0;

			// deactivate
			this->isActive = false;
		}
	}

}

void SandBag::HandleEvent(const SGD::Event* pEvent)
{
	if (pEvent->GetEventID() == "REPAIR_SANDBAGS")
	{
		isActive = true;
		m_fCurrHP = m_fMaxHP;
	}
	if (pEvent->GetEventID() == "UPGRADE_SANDBAG_HEALTH")
	{
		m_fMaxHP += 50;
		m_fCurrHP = m_fMaxHP;
	}

}
