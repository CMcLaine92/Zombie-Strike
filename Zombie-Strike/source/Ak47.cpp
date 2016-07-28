#include "Ak47.h"
#include "MovingObject.h"
#include "CreatePistolBullet.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "GameplayState.h"

Ak47::Ak47(MovingObject* owner)
{
	type = AK47;
	reloadTime = 2.5f;
	currAmmo = 25;
	magSize = 25;
	ammoCapactity = 100;
	recoilTime = 0.1f;
	bulletSpread = 6.0f;
	damage = 34.0f;
	speed = 800.0f;
	lifeTime = 1000.0f;
	m_pOwner = owner;
	owner->AddRef();
	fire_sound = &Game::GetInstance()->rifle_fire;
}


Ak47::~Ak47()
{
}

void Ak47::Fire(float dt)
{
	SGD::AudioManager*	pAudio		= SGD::AudioManager::GetInstance();
	Game*		pGame	= Game::GetInstance();

	if (currAmmo > 0)
	{
		//create bullet message
		if (recoilTimer.GetTime() == 0)
		{
			CreatePistolBullet* pMsg = new CreatePistolBullet(this);
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
