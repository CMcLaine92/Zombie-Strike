#include "GrenadeLauncher.h"
#include "MovingObject.h"
#include "CreateGrenadeBullet.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "GameplayState.h"

GrenadeLauncher::GrenadeLauncher(MovingObject* owner)
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
	fire_sound = &Game::GetInstance()->rpg_fire;
}


GrenadeLauncher::~GrenadeLauncher()
{
}

void GrenadeLauncher::Fire(float dt)
{
	SGD::AudioManager*	pAudio		= SGD::AudioManager::GetInstance();
	Game*		pGame	= Game::GetInstance();

	if (currAmmo > 0)
	{
		//create bullet message
		if (recoilTimer.GetTime() == 0)
		{
			CreateGrenadeBullet* pMsg = new CreateGrenadeBullet(this);
			pMsg->QueueMessage();
			pMsg = nullptr;

			if (pAudio->IsAudioPlaying(*fire_sound) == false)
				voice = pAudio->PlayAudio(*fire_sound, false);

			recoilTimer.AddTime(recoilTime);
			currAmmo--;
			if (currAmmo == 0)
				reloadTimer.AddTime(reloadTime);
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
