#include "Sniper.h"
#include "MovingObject.h"
#include "CreateSniperBullet.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "GameplayState.h"

Sniper::Sniper(MovingObject* owner)
{
	type = SPECIAL;
	reloadTime = 3.5f;
	currAmmo = 5;
	magSize = 5;
	ammoCapactity = 10;
	recoilTime = .5f;
	damage = 100.0f;
	speed = 750.0f;
	lifeTime = 1000.0f;
	m_pOwner = owner;
	owner->AddRef();
	fire_sound = &Game::GetInstance()->sniper_fire;

}


Sniper::~Sniper()
{
	//m_pOwner->Release();
	//m_pOwner = nullptr;
}

void Sniper::Fire(float dt)
{
	SGD::AudioManager*	pAudio		= SGD::AudioManager::GetInstance();
	Game*		pGame	= Game::GetInstance();

	if (currAmmo > 0)
	{
		//create bullet message
		if (recoilTimer.GetTime() == 0)
		{
			CreateSniperBullet* pMsg = new CreateSniperBullet(this);
			pMsg->QueueMessage();
			pMsg = nullptr;

			//if (pAudio->IsAudioPlaying(*fire_sound) == false)
			voice = pAudio->PlayAudio(*fire_sound, false);

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