#include "FatZombie.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "GameplayState.h"
#include "BehaviorManager.h"
#include "BaseBehavior.h"
#include "AnimationManager.h"
#include "Bullet.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "DestroyObjectMessage.h"
#include "Weapon.h"
#include "PukerBlaster.h"
#include "SpawnManager.h"
#include "AnimationManager.h"
#include "Animation.h"
#include "Frame.h"


FatZombie::FatZombie()
{
	health = 200.0f;
	damage = 20.0f;
	//damage = 3.0f;
	//pukeBlaster = new PukerBlaster(this);

	RegisterForEvent("GAME_OVER");
}


FatZombie::~FatZombie()
{
	SetTarget(nullptr);
	UnregisterFromEvent("GAME_OVER");

	
}
void FatZombie::Update(float dt)
{
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();


	
	pukeBlaster.Update(dt);
	if (isAlive)
	{
		if (currBehavior != nullptr)
			currBehavior->Update(dt, this, m_pTarget->GetPosition());

		// possible turret target
		SGD::Event event = { "ASSESS_THREAT", nullptr, this };
		event.SendEventNow(nullptr);

		if ((m_pTarget->GetPosition() - m_ptPosition).ComputeLength() <= 200.0f && this->animation.m_strCurrAnimation.find("Death") == string::npos)
		{
			pukeBlaster.Fire(dt);
		}


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
		pukeBlaster.SetOwner(nullptr);
		

		SpawnManager::GetInstance()->SetEnemiesKilled(SpawnManager::GetInstance()->GetEnemiesKilled() + 1);

	}
	MovingObject::Update(dt);

	
}


/*virtual*/ void FatZombie::HandleEvent(const SGD::Event* pEvent)
{
	if (pEvent->GetEventID() == "GAME_OVER")
	{
		pukeBlaster.SetOwner(nullptr);
	}
}

