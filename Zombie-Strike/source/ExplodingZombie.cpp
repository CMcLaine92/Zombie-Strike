#include "ExplodingZombie.h"
#include "BaseBehavior.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "DestroyObjectMessage.h"
#include "SpawnManager.h"
#include "Bullet.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "GameplayState.h"
#include "BarbedWire.h"
#include "LandMine.h"
#include "House.h"
#include "CreateBloodMsg.h"

ExplodingZombie::ExplodingZombie()
{
	health = 60.0f;
	//damage = 200.0f;
	damage = 20.0f;
}


ExplodingZombie::~ExplodingZombie()
{

}

void ExplodingZombie::Update(float dt)
{
	if (isAlive)
	{
		if (animation.m_strCurrAnimation != "bloodExplosion")
		{
			if (currBehavior != nullptr)
				currBehavior->Update(dt, this, m_pTarget->GetPosition());

			// possible turret target
			SGD::Event event = { "ASSESS_THREAT", nullptr, this };
			event.SendEventNow(nullptr);

		}
		else
		{
			m_vtVelocity = SGD::Vector();
			if (animation.m_nCurrFrame == 7)
			{
				isAlive = false;
			}
		}
		

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


void ExplodingZombie::HandleEvent(const SGD::Event* pEvent)
{

}

/*virtual*/ void ExplodingZombie::HandleCollision(const IBase* pOther)
{
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	if (animation.m_strCurrAnimation != "bloodExplosion")
	{
		if (pOther->GetType() == OBJ_BULLET)
		{
			const Bullet* bullet = dynamic_cast<const Bullet*>(pOther);

			SetAnimation("bloodExplosion");

			if (pAudio->IsAudioPlaying(Game::GetInstance()->zombie_pain) == false)
				pAudio->PlayAudio(Game::GetInstance()->zombie_pain, false);

			CreateBloodMsg* msg = new CreateBloodMsg(m_ptPosition);
			msg->QueueMessage();
			msg = nullptr;
		}
		else if (pOther->GetType() == OBJ_BARBEDWIRE)
		{
			const BarbedWire* barbWire = dynamic_cast<const BarbedWire*>(pOther);
			if (barbWire->IsActive())
			{
				SetAnimation("bloodExplosion");
				MovingObject::HandleCollision(pOther);
			}
		}
		else if (pOther->GetType() == OBJ_SANDBAG)
		{
			const SandBag* sandbag = dynamic_cast<const SandBag*>(pOther);
			if (sandbag->IsActive())
			{
				MovingObject::HandleCollision(pOther);
				SetAnimation("bloodExplosion");
			}
		}

		else if (pOther->GetType() == OBJ_LANDMINE)
		{
			const LandMine* landMine = dynamic_cast<const LandMine*>(pOther);
			if (landMine->IsActive())
			{
				SetAnimation("bloodExplosion");
			}
		}
		else if (pOther->GetType() == OBJ_WALL)
		{
			const House* house = dynamic_cast<const House*>(pOther);

			if (house->IsActive() == true)
				SetAnimation("bloodExplosion");
		}
		else if (pOther->GetType() == OBJ_PLAYER)
		{
			SetAnimation("bloodExplosion");
		}
		else if (pOther->GetType() == OBJ_BASE)
			MovingObject::HandleCollision(pOther);
	}
}