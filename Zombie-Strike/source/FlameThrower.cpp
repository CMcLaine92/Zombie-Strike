#include "FlameThrower.h"
#include "MovingObject.h"
#include "CreateFlameBullet.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "GameplayState.h"

FlameThrower::FlameThrower(MovingObject* owner) : Listener(this)
{
	type = FTHROWER;
	reloadTime = 4.0f;
	currAmmo = 200;
	magSize = 200;
	ammoCapactity = 500;
	recoilTime = .02f;
	bulletSpread = 5.0f;
	damage = 50.0f;
	speed = 500.0f;
	lifeTime = 700.0f;
	m_pOwner = owner;
	owner->AddRef();
	fire_sound = &Game::GetInstance()->flamethrower_fire;
}


FlameThrower::~FlameThrower()
{
	//m_pOwner->Release();
	//m_pOwner = nullptr;
}

void FlameThrower::Fire(float dt)
{
	SGD::AudioManager*	pAudio		= SGD::AudioManager::GetInstance();
	Game*		pGame	= Game::GetInstance();

	if (currAmmo > 0)
	{
		//create bullet message
		if (recoilTimer.GetTime() == 0 && pAudio->IsAudioPlaying(pGame->reload_finish) == false)
		{
			CreateFlameBullet* pMsg = new CreateFlameBullet(this);
			pMsg->QueueMessage();
			pMsg = nullptr;

			if (pAudio->IsAudioPlaying(*fire_sound) == false)
				pAudio->PlayAudio(*fire_sound, false);

			recoilTimer.AddTime(recoilTime);
			currAmmo--;
			if (currAmmo == 0)
			{
				reloadTimer.AddTime(reloadTime);
				reloading = true;
			}
		}
	}
	else
	{
		if (pAudio->IsAudioPlaying(pGame->out_of_ammo) == false && pAudio->IsAudioPlaying(*fire_sound) == false
			&& pAudio->IsAudioPlaying(pGame->reload_begin) == false
			&& pAudio->IsAudioPlaying(pGame->reload_finish) == false)
			pAudio->PlayAudio(pGame->out_of_ammo, false);
	}
}

