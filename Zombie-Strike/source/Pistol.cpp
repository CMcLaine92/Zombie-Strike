#include "Pistol.h"
#include "MovingObject.h"
#include "CreatePistolBullet.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "GameplayState.h"
#define INT_MAX    2147483647

Pistol::Pistol(MovingObject* owner)
{
	type = PISTOL;
	reloadTime = 2.0f;
	currAmmo = 10;
	magSize = 10;
	ammoCapactity = INT_MAX;
	recoilTime = .33f;
	bulletSpread = 5.0f;

	damage = 34.0f;
	speed = 600.0f;
	lifeTime = 700.0f;
	m_pOwner = owner;

	m_pOwner->AddRef();

	fire_sound = &Game::GetInstance()->pistol_fire;
}


Pistol::~Pistol()
{
	//m_pOwner->Release();
	//m_pOwner = nullptr;
}
void Pistol::Fire(float dt)
{
	SGD::AudioManager*	pAudio		= SGD::AudioManager::GetInstance();
	Game*		pGame	= Game::GetInstance();

	if (currAmmo > 0)
	{
		//create bullet message
		if (recoilTimer.GetTime() == 0 && pAudio->IsAudioPlaying(pGame->reload_finish) == false)
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
