#include "House.h"
#include "Game.h"
#include "AnimationManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_Event.h"


House::House()
{
	this->SetType(ObjectType::OBJ_WALL);
	this->SetAnimation("house");

	m_fCurrHP = m_fMaxHP = 500.0f;
	RegisterForEvent("REPAIR_HOUSE");
}

House::~House()
{
	UnregisterFromEvent("REPAIR_HOUSE");
}

void House::Update( float dt )
{
	if (this->isActive == false)
		return;


	SandBag::Update(dt);
}

void House::Render( void )
{
	if (this->isActive == false)
		return;

	SGD::Color healthcolor;
	if (m_fCurrHP == m_fMaxHP)				// 100 -> Normal/Green
		healthcolor = { 255, 255, 255 };

	else if (m_fCurrHP <= m_fMaxHP * 0.25F)	// 0 - 25 -> Red
		healthcolor = { 255, 0, 0 };

	else									// 25 - 99 -> yellow
		healthcolor = { 255, 255, 0 };
	
	//BaseObject::Render();
	AnimationManager::GetInstance()->Render(this->animation, this->m_ptPosition, this->m_fRotation, healthcolor);
	SGD::GraphicsManager::GetInstance()->DrawRectangle(this->GetRect(), SGD::Color(0, 0, 0, 0), SGD::Color(255, 0, 0, 0));
}

void House::HandleCollision( const IBase* pOther )
{
	if (this->isActive == false)
		return;

	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();
	Game* pGame = Game::GetInstance();


	// zombie collision
	if (pOther->GetType() >= ObjectType::OBJ_SLOW_ZOMBIE && pOther->GetType() <= ObjectType::OBJ_TANK_ZOMBIE)
	{
		// lower HP by zombie damage
		pOther->GetType() == ObjectType::OBJ_EXPLODING_ZOMBIE
			? m_fCurrHP -= 200.0f * Game::GetInstance()->DeltaTime()
			: m_fCurrHP -= 10.0f * Game::GetInstance()->DeltaTime();


		// sound

		int sound = rand() % 2;

		switch (sound)
		{
		case 0:
			if (pAudio->IsAudioPlaying(pGame->zombie_hit_house1) == false && pAudio->IsAudioPlaying(pGame->zombie_hit_house2) == false)
				pAudio->PlayAudio(pGame->zombie_hit_house2, false);
			break;

		case 1:
			if (pAudio->IsAudioPlaying(pGame->zombie_hit_house1) == false && pAudio->IsAudioPlaying(pGame->zombie_hit_house2) == false)
				pAudio->PlayAudio(pGame->zombie_hit_house1, false);
			break;

		default:
			break;
		}


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

void House::HandleEvent(const SGD::Event* pEvent)
{
	if (pEvent->GetEventID() == "REPAIR_HOUSE")
	{
		isActive = true;
		m_fCurrHP = m_fMaxHP;
	}
}
