#include "Bullet.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "BaseObject.h"
#include "House.h"
#include "GameplayState.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "AnimationManager.h"
#include "DestroyObjectMessage.h"
#include "../SGD Wrappers/SGD_AudioManager.h"


Bullet::Bullet() : Listener(this)
{
	RegisterForEvent("KILL_ME");
}

Bullet::~Bullet()
{
	if (m_pOwner != nullptr)
	{
		m_pOwner->Release();
		m_pOwner = nullptr;
	}
	
	UnregisterFromEvent("KILL_ME");
}

/*virtual*/ void Bullet::Update(float dt) /*override*/
{
	//MovingObject::Update(dt);
	//lifeTime -= m_vtVelocity.ComputeLength() * dt;
	m_ptPosition += m_vtVelocity * dt;
	AnimationManager::GetInstance()->Update(animation, dt, this);

	if (IsDead())
	{
	

			DestroyObjectMessage* pMsg = new DestroyObjectMessage{ this };
			pMsg->QueueMessage();
			pMsg = nullptr;
		
	
	}
}

/*virtual*/ void Bullet::HandleCollision(const IBase* pOther)	/*override*/
{
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	// other stuff
	if (pOther->GetType() == ObjectType::OBJ_BASE || pOther->GetType() == ObjectType::OBJ_WALL)
	{
		const House* house = dynamic_cast<const House*>(pOther);

		if (house->IsActive() == true)
		{
			pAudio->PlayAudio(Game::GetInstance()->bullet_hit_house, false);

			DestroyObjectMessage* dMsg = new DestroyObjectMessage{ this };
			dMsg->QueueMessage();
			dMsg = nullptr;
			return;
		}
	}


	if (this->type != ObjectType::OBJ_VOMIT)
	{
		// player
		if (pOther->GetType() == OBJ_SLOW_ZOMBIE ||
			pOther->GetType() == OBJ_FAST_ZOMBIE ||
			pOther->GetType() == OBJ_FAT_ZOMBIE ||
			pOther->GetType() == OBJ_TANK_ZOMBIE ||
			pOther->GetType() == OBJ_EXPLODING_ZOMBIE)
		{
			if (GetOwner() != pOther)
			{
				if (pAudio->IsAudioPlaying(Game::GetInstance()->bullet_hit_zombie) == false)
					pAudio->PlayAudio(Game::GetInstance()->bullet_hit_zombie, false);

				penetratingPower--;
				if (penetratingPower < 0)
				{
					DestroyObjectMessage* dMsg = new DestroyObjectMessage{ this };
					dMsg->QueueMessage();
					dMsg = nullptr;
				}
				
			}
		}
		


	}
	else if (this->type == ObjectType::OBJ_VOMIT)
	{
		// zombie
		if (pOther->GetType() == OBJ_PLAYER)
		{
			if (GetOwner() != pOther)
			{
				if (pAudio->IsAudioPlaying(Game::GetInstance()->vomit_hit_player) == false)
					pAudio->PlayAudio(Game::GetInstance()->vomit_hit_player, false);

	
				DestroyObjectMessage* dMsg = new DestroyObjectMessage{ this };
				dMsg->QueueMessage();
				dMsg = nullptr;
			}
		}
	}
}

/*virtual*/ void Bullet::HandleEvent(const SGD::Event* pEvent)
{
	if (pEvent->GetEventID() == "KILL_ME")
	{
		
		DestroyObjectMessage* dMsg = new DestroyObjectMessage{ this };
		dMsg->QueueMessage();
		dMsg = nullptr;
	}
}

void Bullet::SetOwner(MovingObject* _owner)
{
	if (m_pOwner != nullptr)
	{
		m_pOwner->Release();
		m_pOwner = nullptr;
	}

	m_pOwner = _owner;
	m_pOwner->AddRef();
}

bool Bullet::IsDead()
{
	SGD::Rectangle world = { 0, 0,
		GameplayState::GetInstance()->GetWorldSize().width,
		GameplayState::GetInstance()->GetWorldSize().height };
	SGD::Rectangle rect = GetRect();
	rect.Offset(GameplayState::GetInstance()->GetCamera()->GetPosition().x, GameplayState::GetInstance()->GetCamera()->GetPosition().y);
	if (rect.IsIntersecting(world))
		return false;
	else
		return true;

}