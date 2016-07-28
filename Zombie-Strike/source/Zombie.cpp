#include "Zombie.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "GameplayState.h"
#include "BehaviorManager.h"
#include "BaseBehavior.h"
#include "AnimationManager.h"
#include "Animation.h"
#include "Frame.h"
#include "Bullet.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "DestroyObjectMessage.h"
#include "Game.h"
#include "BarbedWire.h"
#include "LandMine.h"
#include "SandBag.h"
#include "House.h"
#include "SpawnManager.h"
#include "CreateBloodMsg.h"


Zombie::Zombie() : Listener(this)
{
	damage = 10.0f;
	//damage = 2.0f;
	health = 100.0f;
}


Zombie::~Zombie() 
{
	SetTarget(nullptr);
	
}
void Zombie::Update(float dt)
{
	if (isAlive)
	{
		if (currBehavior != nullptr)
			currBehavior->Update(dt, this, m_pTarget->GetPosition());

		// possible turret target
		SGD::Event event = { "ASSESS_THREAT", nullptr, this };
		event.SendEventNow(nullptr);


		// death animation
		int		numframes	= AnimationManager::GetInstance()->GetAnimation(this->animation.m_strCurrAnimation)->GetFrames().size();
		numframes--;
		float	deathdur	= AnimationManager::GetInstance()->GetAnimation(this->animation.m_strCurrAnimation)->GetFrames()[numframes]->GetDuration();
		string	deathanim	= this->animation.m_strCurrAnimation;

		if (deathanim.find("Death") != string::npos && this->animation.m_nCurrFrame == numframes && this->animation.m_fCurrDuration >= deathdur)
			isAlive = false;
	}
	else
	{
		DestroyObjectMessage* dMsg = new DestroyObjectMessage{ this };
		dMsg->QueueMessage();
		dMsg = nullptr;

		SpawnManager::GetInstance()->SetEnemiesKilled(SpawnManager::GetInstance()->GetEnemiesKilled() + 1);
	}

	MovingObject::Update(dt);
	
}
void Zombie::RetrieveBehavior(std::string name)
{

	if (currBehavior != nullptr)
		currBehavior = nullptr;

	currBehavior = BehaviorManager::GetInstance()->GetBehaviors()[name];
}

/*virtual*/ void Zombie::HandleEvent(const SGD::Event* pEvent)
{
	/*if (pEvent->GetEventID() == "BARBWIRE")
	{
		health -= 10.0f; 
		if (health <= 0)
			isAlive = false;
		
	}*/
}

/*virtual*/ void Zombie::HandleCollision(const IBase* pOther)
{
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	if (pOther->GetType() == OBJ_BULLET)
	{
		const Bullet* bullet = dynamic_cast<const Bullet*>(pOther);

		health -= bullet->GetDamage();
		if (health <= 0.0f)
		{
			this->SetAnimation(this->animation.m_strCurrAnimation + "Death");
			this->RetrieveBehavior("wait");
			//isAlive = false;
		}

		if (pAudio->IsAudioPlaying(Game::GetInstance()->zombie_pain) == false)
			pAudio->PlayAudio(Game::GetInstance()->zombie_pain, false);

		CreateBloodMsg* msg = new CreateBloodMsg(m_ptPosition);
		msg->QueueMessage();
		msg = nullptr;

		
	}
	if (pOther->GetType() == OBJ_EXPLODING_ZOMBIE)
	{
		const BaseObject* ptr = dynamic_cast<const BaseObject*>(pOther);

		if (ptr->GetAnimation() == "bloodExplosion")
		{
			this->SetAnimation(this->animation.m_strCurrAnimation + "Death");
			this->RetrieveBehavior("wait");
			//isAlive = false;
		}
	}
	if (pOther->GetType() == OBJ_BARBEDWIRE)
	{
		const BarbedWire* barbWire = dynamic_cast<const BarbedWire*>(pOther);
		if (barbWire->IsActive())
		{
			health -= barbWire->GetDamage() * Game::GetInstance()->DeltaTime();
			if (health <= 0)
			{
				this->SetAnimation(this->animation.m_strCurrAnimation + "Death");
				this->RetrieveBehavior("wait");
				//isAlive = false;
			}
			MovingObject::HandleCollision(pOther);
		}
	}
	if (pOther->GetType() == OBJ_SANDBAG)
	{
		const SandBag* sandbag = dynamic_cast<const SandBag*>(pOther);
		if (sandbag->IsActive())
			MovingObject::HandleCollision(pOther);
	}

	if (pOther->GetType() == OBJ_LANDMINE)
	{
		const LandMine* landMine = dynamic_cast<const LandMine*>(pOther);
		if (landMine->IsActive())
		{
			this->SetAnimation(this->animation.m_strCurrAnimation + "Death");
			this->RetrieveBehavior("wait");
			//isAlive = false;
		}
	}

	else if (pOther->GetType() == OBJ_WALL)
	{
		const House* house = dynamic_cast<const House*>(pOther);

		if (house->IsActive() == true)
			MovingObject::HandleCollision(pOther);
	}
	else if (pOther->GetType() == OBJ_BASE)
			MovingObject::HandleCollision(pOther);
	

}

void Zombie::SetTarget(BaseObject* target)
{
	if (m_pTarget != nullptr)
	{
		m_pTarget->Release();
		m_pTarget = nullptr;
	}
	m_pTarget = target;
	if (m_pTarget != nullptr)
	{
		m_pTarget->AddRef();
	}
}