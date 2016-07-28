#include "AutoShotgun.h"
#include "MovingObject.h"
#include "CreateShotgunBullet.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "GameplayState.h"

AutoShotgun::AutoShotgun(MovingObject* owner)
{
	type = SHOTGUN;
	reloadTime = 4.0f;
	currAmmo = 6;
	magSize = 6;
	ammoCapactity = 24;
	recoilTime = 1.0f;
	bulletSpread = 15.0f;
	damage = 50.0f;
	speed = 700.0f;
	lifeTime = 400.0f;
	m_pOwner = owner;
	owner->AddRef();
	fire_sound = &Game::GetInstance()->shotgun_fire;
}


AutoShotgun::~AutoShotgun()
{
}

void AutoShotgun::Fire(float dt)
{
	SGD::AudioManager*	pAudio		= SGD::AudioManager::GetInstance();
	Game*		pGame	= Game::GetInstance();

	if (currAmmo > 0)
	{
		//create bullet message
		if (recoilTimer.GetTime() == 0)
		{
			CreateShotgunBullet* pMsg = new CreateShotgunBullet(this);
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
