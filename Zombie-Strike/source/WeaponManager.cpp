#include "WeaponManager.h"
#include "MovingObject.h"

#include "Pistol.h"
#include "Revolver.h"

#include "Shotgun.h"
#include "SawnOff.h"
#include "AutoShotgun.h"

#include "Sniper.h"
#include "FlameThrower.h"
#include "GrenadeLauncher.h"

#include "P90.h"
#include "UZI.h"
#include "Tech9.h"

#include "AssaultRifle.h"
#include "Ak47.h"
#include "LMG.h"

#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "HTPGameState.h"

#include "GameplayState.h"
#include "Game.h"

#include "BitmapFont.h"

#include <cassert>
#include <sstream>

using namespace std;

/*static*/ WeaponManager* WeaponManager::GetInstance(void)
{
	static WeaponManager s_Instance;
	return &s_Instance;
}

void WeaponManager::Initialize(MovingObject& owner)
{
	m_hHudWpn = Game::GetInstance()->m_hHudWpn;
	m_hWpnSwitch = Game::GetInstance()->m_hWpnSwitch;

	SetOwner(&owner);

	AddWeapons(CreatePistol());
	AddWeapons(CreateRevolver());
	AddWeapons(CreateSawnOff());
	AddWeapons(CreatePumpShotgun());
	AddWeapons(CreateAutoShotgun());
	AddWeapons(CreateMac10());
	AddWeapons(CreateTech9());
	AddWeapons(CreateP90());
	AddWeapons(CreateAK47());
	AddWeapons(CreateAssaultRifle());
	AddWeapons(CreateLMG());
	AddWeapons(CreateSniper());
	AddWeapons(CreateFlameThrower());
	AddWeapons(CreateGrenadeLauncher());

	//m_aWpnInventory[0] = m_vWeapons[0];


	curIndex = 0;
}

void WeaponManager::Render()
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();

	const BitmapFont * bFont = Game::GetInstance()->GetFont();

	SGD::Rectangle equipRect = { Game::GetInstance()->GetScreenWidth() - 275.0f, Game::GetInstance()->GetScreenHeight() - 150.0f, Game::GetInstance()->GetScreenWidth() - 10, Game::GetInstance()->GetScreenHeight() - 10 };

	pGraphics->DrawRectangle(equipRect, { 255, 255, 255 }, { 0, 0, 255 });

	for (unsigned int i = 0; i < m_vWeapons.size(); i++)
	{
		if (m_vWeapons[curIndex]->GetGunType() == m_vWeapons[i]->GetGunType() && m_vWeapons[curIndex]->GetEquipped() == true)
		{
			pGraphics->DrawTextureSection(m_hHudWpn, { Game::GetInstance()->GetScreenWidth() - 150.0f, Game::GetInstance()->GetScreenHeight() - 150.0f },
				m_vWeapons[curIndex]->GetRenderRect(), {}, {}, {}, { .5f, .5f });

			stringstream magSize;
			magSize << m_vWeapons[curIndex]->GetCurrAmmo() << "|";

			SGD::Point magPos = { equipRect.left + 10, equipRect.bottom - 50 };
			SGD::Point ammoPos = { equipRect.left + 71, equipRect.bottom - 50 };

			if (m_vWeapons[curIndex]->GetCurrAmmo() < 10)
			{
				magPos.x = equipRect.left + 28;
			}

			bFont->Draw(magSize.str().c_str(), magPos, 1.0f, { 0, 0, 0 });

			stringstream ammoCap;
			ammoCap << m_vWeapons[curIndex]->GetTotalAmmo();

			if (m_vWeapons[curIndex]->GetTotalAmmo() < 10)
			{
				ammoPos.x = equipRect.left + 58;
			}

			else if (m_vWeapons[curIndex]->GetTotalAmmo() < 100)
			{
				ammoPos.x = equipRect.left + 68;
			}

			else
			{
				ammoPos.x = equipRect.left + 71;
			}

			if (m_vWeapons[curIndex]->GetType() == PISTOL)
			{
				bFont->Draw("INF", ammoPos, 1.0f, { 0, 0, 0 });
			}

			else
				bFont->Draw(ammoCap.str().c_str(), ammoPos, 1.0f, { 0, 0, 0 });

			if (m_vWeapons[curIndex]->GetCurrAmmo() == 0 && m_vWeapons[curIndex]->GetTotalAmmo() > 0)
			{
				bFont->Draw("RELOAD", { Game::GetInstance()->GetScreenWidth() - 275, Game::GetInstance()->GetScreenHeight() - 150 }, 1.5f, { 200, 0, 0 });
			}

			if (m_vWeapons[curIndex]->GetTotalAmmo() == 0 && m_vWeapons[curIndex]->GetCurrAmmo() <= 0)
			{
				bFont->Draw("OUT OF AMMO", { Game::GetInstance()->GetScreenWidth() - 275, Game::GetInstance()->GetScreenHeight() - 150 }, .75f, { 200, 0, 0 });
			}


		}
	}

	int size = 75;
	float sWidth = Game::GetInstance()->GetScreenWidth() / 2 - size * 2 - 50;
	float sHeight = Game::GetInstance()->GetScreenHeight() - 10;

	SGD::Rectangle unEquip;

	for (unsigned int j = 0; j < 5; j++)
	{
		unEquip = { sWidth + size*j, sHeight - 75, sWidth + size*j + size, sHeight };
		pGraphics->DrawRectangle(unEquip, { 255, 255, 255 }, { 0, 0, 255 });

		//if (m_vWeapons[equipIndex]->GetObtained() == false)
		//{
		//	pGraphics->DrawRectangle({ sWidth + size*j, sHeight - size, sWidth + size*j + size, sHeight }, { 175, 0, 0, 0 });
		//}
	}


	for (unsigned int j = 0; j < 5; j++)
	{
		for (unsigned int i = equipIndex; i < m_vWeapons.size(); i++)
		{
			unEquip = { sWidth + size*j, sHeight - 75, sWidth + size*j + size, sHeight };
			//pGraphics->DrawRectangle(unEquip, { 255, 255, 255 }, { 0, 0, 255 });

			if (m_vWeapons[i]->GetObtained() == true && m_vWeapons[i]->GetEquipped() == true)
			{
				SGD::Rectangle imageRect = m_vWeapons[i]->GetRenderRect();				

				if (m_vWeapons[i]->GetGunType() == m_vWeapons[curIndex]->GetGunType())
				{
					pGraphics->DrawTextureSection(m_hHudWpn, { sWidth + size*j, sHeight - size },
						imageRect, {}, {}, {}, { .25f, .25f });
				}

				else
				{
					pGraphics->DrawTextureSection(m_hHudWpn, { sWidth + size*j, sHeight - size },
						imageRect, {}, {}, {}, { .25f, .25f });


				}
				
				equipIndex++;
				break;
			} 

			stringstream drawIndex;
			drawIndex << j + 1;
			bFont->Draw(drawIndex.str().c_str(), { unEquip.left + 1, unEquip.top - 5 }, .5f, { 150, 155, 155 });

			equipIndex++;
		}
	}

	equipIndex = 0;

	for (unsigned int i = 0; i < 5; i++)
	{
		for (unsigned int j = 0; j < m_vWeapons.size(); j++)
		{
			SGD::Rectangle unEquip = { sWidth + size*i, sHeight - 75, sWidth + size*i + size, sHeight };

			stringstream drawIndex;
			drawIndex << i + 1;

			bFont->Draw(drawIndex.str().c_str(), { unEquip.left + 1, unEquip.top - 5 }, .5f, { 150, 155, 155 });
		}
	}


}

void WeaponManager::Input()
{
	SGD::InputManager * pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Q) == true || pInput->IsButtonPressed(0, 4) == true)
	{
		curIndex--;

		if (curIndex < 0)
		{
			curIndex = m_vWeapons.size() - 1;
		}


		if (pAudio->IsAudioPlaying(m_hWpnSwitch) == false)
		{
			pAudio->PlayAudio(m_hWpnSwitch, false);
		}

		while (m_vWeapons[curIndex]->GetEquipped() != true)
		{
			curIndex--;

			if (curIndex < 0)
			{
				curIndex = m_vWeapons.size() - 1;
			}
		}
	}

	if (pInput->IsKeyPressed(SGD::Key::E) == true || pInput->IsButtonPressed(0, 5) == true)
	{
		curIndex++;


		if (curIndex > (int)m_vWeapons.size() - 1)
		{
			curIndex = 0;
		}

		if (pAudio->IsAudioPlaying(m_hWpnSwitch) == false)
		{
			pAudio->PlayAudio(m_hWpnSwitch, false);
		}

		while (m_vWeapons[curIndex]->GetEquipped() != true)
		{
			curIndex++;

			if (curIndex > (int)m_vWeapons.size() - 1)
			{
				curIndex = 0;
			}
		}
	}

	if (pInput->IsKeyPressed(SGD::Key::R) == true && m_vWeapons[curIndex]->GetCurrAmmo() < m_vWeapons[curIndex]->GetMagSize())
	{
		//GetSelected()->SetCurrAmmo(0);
		//GetSelected()->GetReloadTimer().AddTime(GetSelected()->GetReloadTime());
		//m_vWeapons[curIndex]->SetCurrAmmo(0);
		//m_vWeapons[curIndex]->GetReloadTimer().AddTime(m_vWeapons[curIndex]->GetReloadTime());
	}
}

void WeaponManager::Update(float dt)
{
	Input();

	for (unsigned int i = 0; i < m_vWeapons.size(); i++)
	{
		m_vWeapons[i]->Update(dt);

		//if (m_vWeapons[i]->GetType() == PISTOL )
		//{
		//	if (m_vWeapons[i]->GetGunType() == GLOCK && m_vWeapons[i]->GetEquipped() == true)
		//	{
		//			for (unsigned int j = 0; j < m_vWeapons.size(); j++)
		//			{
		//				if (m_vWeapons[j]->GetGunType() != GLOCK && m_vWeapons[j]->GetType() == PISTOL)
		//				{
		//					m_vWeapons[j]->SetEquipped(false);
		//				}
		//			}
		//	}
		//}

		//else if (m_vWeapons[i]->GetType() == SMG)
		//{

		//}

		//else if (m_vWeapons[i]->GetType() == )
		//{

		//}
	}

}

void WeaponManager::Exit()
{
	for (unsigned int i = 0; i < m_vWeapons.size(); i++)
	{
		delete m_vWeapons[i];
		m_vWeapons[i] = nullptr;

	}

	m_vWeapons.clear();

	m_pOwner->Release();
	m_pOwner = nullptr;
}

void WeaponManager::SelectWeapon(int index)
{

	for (unsigned int i = 0; i < m_vWeapons.size(); i++)
	{
		if (m_vWeapons[i]->GetType() == index && m_vWeapons[i]->GetEquipped() == true)
		{
			curIndex = i;
			break;
		}
	}
	
}

void WeaponManager::AddWeapons(Weapon* wpn)
{
	m_vWeapons.push_back(wpn);
}

Weapon * WeaponManager::CreateAssaultRifle()
{
	AssaultRifle * ar = new AssaultRifle(GetOwner());

	GamerProfile* profile;
	if (GameplayState::GetInstance()->GetGameMode() == true)
		profile = &Game::GetInstance()->GetStoryProfile();
	else
		profile = &Game::GetInstance()->GetSurvivalProfile();


	//ar->SetObtained(profile->m16.isBought);
	ar->SetObtained(profile->m16.isBought);

	ar->SetEquipped(false);
	ar->SetAutomatic(true);
	ar->SetGunType(M16);
	ar->SetType(ASSUALT_RIFLE);
	ar->SetRenderRect(SetImageRect(300, 300, 0, 1));
	ar->SetMagSize(profile->m16.magSize.upgradedSkill.stat);
	ar->SetCurrAmmo(profile->m16.magSize.upgradedSkill.stat);
	ar->SetTotalAmmo(profile->m16.totalAmmo.upgradedSkill.stat);
	ar->SetDamage(profile->m16.damage.upgradedSkill.stat);
	ar->SetBulletSpread(profile->m16.bulletSpread.upgradedSkill.stat);
	ar->SetAmmoCap(profile->m16.ammoCap.upgradedSkill.stat);
	ar->SetRecoilTime(profile->m16.recoilTime.upgradedSkill.stat);
	ar->SetReloadTime(profile->m16.reloadTime.upgradedSkill.stat);
	return ar;
}
Weapon * WeaponManager::CreateAK47()
{
	GamerProfile* profile;
	if (GameplayState::GetInstance()->GetGameMode() == true)
		profile = &Game::GetInstance()->GetStoryProfile();
	else
		profile = &Game::GetInstance()->GetSurvivalProfile();

	AssaultRifle * ar = new AssaultRifle(GetOwner());

	//ar->SetObtained(profile->m16.isBought);
	ar->SetObtained(profile->ak47.isBought);

	ar->SetEquipped(false);
	ar->SetAutomatic(true);
	ar->SetGunType(AK47);
	ar->SetType(ASSUALT_RIFLE);
	ar->SetRenderRect(SetImageRect(300, 300, 0, 1));
	ar->SetMagSize(profile->ak47.magSize.upgradedSkill.stat);
	ar->SetCurrAmmo(profile->ak47.magSize.upgradedSkill.stat);
	ar->SetTotalAmmo(profile->ak47.totalAmmo.upgradedSkill.stat);
	ar->SetDamage(profile->ak47.damage.upgradedSkill.stat);
	ar->SetBulletSpread(profile->ak47.bulletSpread.upgradedSkill.stat);
	ar->SetAmmoCap(profile->ak47.ammoCap.upgradedSkill.stat);
	ar->SetRecoilTime(profile->ak47.recoilTime.upgradedSkill.stat);
	ar->SetReloadTime(profile->ak47.reloadTime.upgradedSkill.stat);
	return ar;
}
Weapon * WeaponManager::CreateLMG()
{
	AssaultRifle * ar = new AssaultRifle(GetOwner());
	GamerProfile* profile;
	if (GameplayState::GetInstance()->GetGameMode() == true)
		profile = &Game::GetInstance()->GetStoryProfile();
	else
		profile = &Game::GetInstance()->GetSurvivalProfile();


	//ar->SetObtained(profile->m16.isBought);
	ar->SetObtained(profile->lmg.isBought);

	ar->SetEquipped(false);
	ar->SetAutomatic(true);
	ar->SetGunType(LIGHT_MG);
	ar->SetType(ASSUALT_RIFLE);
	ar->SetRenderRect(SetImageRect(300, 300, 0, 1));
	ar->SetMagSize(profile->lmg.magSize.upgradedSkill.stat);
	ar->SetCurrAmmo(profile->lmg.magSize.upgradedSkill.stat);
	ar->SetTotalAmmo(profile->lmg.totalAmmo.upgradedSkill.stat);
	ar->SetDamage(profile->lmg.damage.upgradedSkill.stat);
	ar->SetBulletSpread(profile->lmg.bulletSpread.upgradedSkill.stat);
	ar->SetAmmoCap(profile->lmg.ammoCap.upgradedSkill.stat);
	ar->SetRecoilTime(profile->lmg.recoilTime.upgradedSkill.stat);
	ar->SetReloadTime(profile->lmg.reloadTime.upgradedSkill.stat);
	return ar;
}

Weapon * WeaponManager::CreatePistol()
{
	GamerProfile* profile;
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		profile = &Game::GetInstance()->GetTutorialProfile();
	else
	{
		if (GameplayState::GetInstance()->GetGameMode() == true)
			profile = &Game::GetInstance()->GetStoryProfile();
		else
			profile = &Game::GetInstance()->GetSurvivalProfile();
	}
	

	Pistol * pistol = new Pistol(GetOwner());

	//pistol->SetOwner(GetOwner());
	//pistol->SetObtained(profile->m16.isBought);
	pistol->SetObtained(true);
	pistol->SetAutomatic(false);

	pistol->SetEquipped(true);
	pistol->SetGunType(GLOCK);
	pistol->SetType(PISTOL);
	pistol->SetRenderRect(SetImageRect(300, 300, 1, 3));
	pistol->SetCurrAmmo(profile->pistol.magSize.upgradedSkill.stat);
	pistol->SetReloadTime(profile->pistol.reloadTime.upgradedSkill.stat);
	pistol->SetRecoilTime(profile->pistol.recoilTime.upgradedSkill.stat);
	pistol->SetTotalAmmo(INT_MAX);

	return pistol;
}
Weapon * WeaponManager::CreateRevolver()
{
	GamerProfile* profile;
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		profile = &Game::GetInstance()->GetTutorialProfile();
	else
	{
		if (GameplayState::GetInstance()->GetGameMode() == true)
			profile = &Game::GetInstance()->GetStoryProfile();
		else
			profile = &Game::GetInstance()->GetSurvivalProfile();
	}

	Pistol* revolver = new Pistol(GetOwner());

	//revolver->SetObtained(profile->revolver.isBought);
	revolver->SetObtained(profile->revolver.isBought);
	revolver->SetAutomatic(false);
	revolver->SetEquipped(false);
	revolver->SetGunType(REVOLVER);
	revolver->SetType(PISTOL);
	revolver->SetRenderRect(SetImageRect(300, 300, 0, 1));
	revolver->SetMagSize(profile->revolver.magSize.upgradedSkill.stat);
	revolver->SetCurrAmmo(profile->revolver.magSize.upgradedSkill.stat);
	revolver->SetTotalAmmo(profile->revolver.totalAmmo.upgradedSkill.stat);
	revolver->SetDamage(profile->revolver.damage.upgradedSkill.stat);
	revolver->SetAmmoCap(profile->revolver.ammoCap.upgradedSkill.stat);
	revolver->SetRecoilTime(profile->revolver.recoilTime.upgradedSkill.stat);
	revolver->SetReloadTime(profile->revolver.reloadTime.upgradedSkill.stat);
	revolver->SetPenPower(profile->revolver.penPower.upgradedSkill.stat);

	return revolver;
}

Weapon * WeaponManager::CreatePumpShotgun()
{
	GamerProfile* profile;
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		profile = &Game::GetInstance()->GetTutorialProfile();
	else
	{
		if (GameplayState::GetInstance()->GetGameMode() == true)
			profile = &Game::GetInstance()->GetStoryProfile();
		else
			profile = &Game::GetInstance()->GetSurvivalProfile();
	}


	Shotgun * shotty = new Shotgun(GetOwner());

	//shotty->SetObtained(profile->shotty.isBought);
	shotty->SetObtained(profile->pumpShotgun.isBought);
	shotty->SetAutomatic(false);
	shotty->SetEquipped(false);
	shotty->SetGunType(PUMP);
	shotty->SetType(SHOTGUN);
	shotty->SetRenderRect(SetImageRect(300, 300, 0, 2));
	shotty->SetCurrAmmo(profile->pumpShotgun.magSize.upgradedSkill.stat);
	shotty->SetMagSize(profile->pumpShotgun.magSize.upgradedSkill.stat);
	shotty->SetRecoilTime(profile->pumpShotgun.recoilTime.upgradedSkill.stat);
	shotty->SetReloadTime(profile->pumpShotgun.reloadTime.upgradedSkill.stat);
	shotty->SetBulletSpread(profile->pumpShotgun.bulletSpread.upgradedSkill.stat);
	shotty->SetAmmoCap(profile->pumpShotgun.ammoCap.upgradedSkill.stat);
	shotty->SetDamage(profile->pumpShotgun.damage.upgradedSkill.stat);
	shotty->SetTotalAmmo(profile->pumpShotgun.totalAmmo.upgradedSkill.stat);

	return shotty;
}
Weapon * WeaponManager::CreateAutoShotgun()
{
	GamerProfile* profile;
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		profile = &Game::GetInstance()->GetTutorialProfile();
	else
	{
		if (GameplayState::GetInstance()->GetGameMode() == true)
			profile = &Game::GetInstance()->GetStoryProfile();
		else
			profile = &Game::GetInstance()->GetSurvivalProfile();
	}

	Shotgun * shotty = new Shotgun(GetOwner());

	shotty->SetObtained(profile->autoShotgun.isBought);

	shotty->SetObtained(false);
	shotty->SetAutomatic(false);
	shotty->SetEquipped(false);
	shotty->SetGunType(AUTO);
	shotty->SetType(SHOTGUN);
	shotty->SetRenderRect(SetImageRect(300, 300, 0, 2));
	shotty->SetCurrAmmo(profile->autoShotgun.magSize.upgradedSkill.stat);
	shotty->SetMagSize(profile->autoShotgun.magSize.upgradedSkill.stat);
	shotty->SetRecoilTime(profile->autoShotgun.recoilTime.upgradedSkill.stat);
	shotty->SetReloadTime(profile->autoShotgun.reloadTime.upgradedSkill.stat);
	shotty->SetBulletSpread(profile->autoShotgun.bulletSpread.upgradedSkill.stat);
	shotty->SetAmmoCap(profile->autoShotgun.ammoCap.upgradedSkill.stat);
	shotty->SetDamage(profile->autoShotgun.damage.upgradedSkill.stat);
	shotty->SetTotalAmmo(profile->autoShotgun.totalAmmo.upgradedSkill.stat);

	return shotty;
}
Weapon * WeaponManager::CreateSawnOff()
{
	GamerProfile* profile;
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		profile = &Game::GetInstance()->GetTutorialProfile();
	else
	{
		if (GameplayState::GetInstance()->GetGameMode() == true)
			profile = &Game::GetInstance()->GetStoryProfile();
		else
			profile = &Game::GetInstance()->GetSurvivalProfile();
	}


	Shotgun * shotty = new Shotgun(GetOwner());

	shotty->SetObtained(profile->sawnoff.isBought);
	shotty->SetAutomatic(false);
	shotty->SetEquipped(false);
	shotty->SetGunType(SAWN);
	shotty->SetType(SHOTGUN);
	shotty->SetRenderRect(SetImageRect(300, 300, 0, 2));
	shotty->SetRecoilTime(profile->sawnoff.recoilTime.upgradedSkill.stat);
	shotty->SetReloadTime(profile->sawnoff.reloadTime.upgradedSkill.stat);
	shotty->SetBulletSpread(profile->sawnoff.bulletSpread.upgradedSkill.stat);
	shotty->SetAmmoCap(profile->sawnoff.ammoCap.upgradedSkill.stat);
	shotty->SetDamage(profile->sawnoff.damage.upgradedSkill.stat);
	shotty->SetTotalAmmo(profile->sawnoff.totalAmmo.upgradedSkill.stat);
	shotty->SetCurrAmmo(2);
	shotty->SetMagSize(2);


	return shotty;
}

Weapon * WeaponManager::CreateSniper()
{
	GamerProfile* profile;
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		profile = &Game::GetInstance()->GetTutorialProfile();
	else
	{
		if (GameplayState::GetInstance()->GetGameMode() == true)
			profile = &Game::GetInstance()->GetStoryProfile();
		else
			profile = &Game::GetInstance()->GetSurvivalProfile();
	}

	Sniper * sniper = new Sniper(GetOwner());

	sniper->SetObtained(profile->sniper.isBought);
	
	sniper->SetAutomatic(false);
	sniper->SetEquipped(false);
	sniper->SetGunType(SNIPER);
	sniper->SetType(SPECIAL);
	sniper->SetRenderRect(SetImageRect(300, 300, 0, 1));
	sniper->SetMagSize(profile->sniper.magSize.upgradedSkill.stat);
	sniper->SetCurrAmmo(profile->sniper.magSize.upgradedSkill.stat);
	sniper->SetTotalAmmo(profile->sniper.totalAmmo.upgradedSkill.stat);
	sniper->SetDamage(profile->sniper.damage.upgradedSkill.stat);
	sniper->SetBulletSpread(profile->sniper.bulletSpread.upgradedSkill.stat);
	sniper->SetAmmoCap(profile->sniper.ammoCap.upgradedSkill.stat);
	sniper->SetRecoilTime(profile->sniper.recoilTime.upgradedSkill.stat);
	sniper->SetReloadTime(profile->sniper.reloadTime.upgradedSkill.stat);
	sniper->SetPenPower(profile->sniper.penPower.upgradedSkill.stat);

	return sniper;
}
Weapon * WeaponManager::CreateFlameThrower()
{
	GamerProfile* profile;
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		profile = &Game::GetInstance()->GetTutorialProfile();
	else
	{
		if (GameplayState::GetInstance()->GetGameMode() == true)
			profile = &Game::GetInstance()->GetStoryProfile();
		else
			profile = &Game::GetInstance()->GetSurvivalProfile();
	}

	FlameThrower * ft = new FlameThrower(GetOwner());

	ft->SetObtained(profile->flameThrower.isBought);
	
	ft->SetAutomatic(true);
	ft->SetEquipped(false);
	ft->SetGunType(FTHROWER);
	ft->SetType(SPECIAL);
	ft->SetRenderRect(SetImageRect(300, 300, 0, 0));
	ft->SetMagSize(profile->flameThrower.magSize.upgradedSkill.stat);
	ft->SetCurrAmmo(profile->flameThrower.magSize.upgradedSkill.stat);
	ft->SetTotalAmmo(profile->flameThrower.totalAmmo.upgradedSkill.stat);
	ft->SetDamage(profile->flameThrower.damage.upgradedSkill.stat);
	ft->SetBulletSpread(profile->flameThrower.bulletSpread.upgradedSkill.stat);
	ft->SetSpeed(profile->flameThrower.bulletVelocity.upgradedSkill.stat);

	ft->SetAmmoCap(profile->flameThrower.ammoCap.upgradedSkill.stat);
	ft->SetReloadTime(profile->flameThrower.reloadTime.upgradedSkill.stat);


	return ft;
}
Weapon * WeaponManager::CreateGrenadeLauncher()
{
	GamerProfile* profile;
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		profile = &Game::GetInstance()->GetTutorialProfile();
	else
	{
		if (GameplayState::GetInstance()->GetGameMode() == true)
			profile = &Game::GetInstance()->GetStoryProfile();
		else
			profile = &Game::GetInstance()->GetSurvivalProfile();
	}

	GrenadeLauncher * nadeLauncher = new GrenadeLauncher(GetOwner());

	nadeLauncher->SetObtained(profile->nadeLauncher.isBought);
	
	nadeLauncher->SetAutomatic(false);
	nadeLauncher->SetEquipped(false);
	nadeLauncher->SetGunType(GLAUNCHER);
	nadeLauncher->SetType(SPECIAL);
	nadeLauncher->SetRenderRect(SetImageRect(300, 300, 0, 1));
	nadeLauncher->SetMagSize(profile->nadeLauncher.magSize.upgradedSkill.stat);
	nadeLauncher->SetCurrAmmo(profile->nadeLauncher.magSize.upgradedSkill.stat);
	nadeLauncher->SetTotalAmmo(profile->nadeLauncher.totalAmmo.upgradedSkill.stat);
	nadeLauncher->SetDamage(profile->nadeLauncher.damage.upgradedSkill.stat);
	nadeLauncher->SetAmmoCap(profile->nadeLauncher.ammoCap.upgradedSkill.stat);
	nadeLauncher->SetReloadTime(profile->nadeLauncher.reloadTime.upgradedSkill.stat);

	return nadeLauncher;
}

Weapon * WeaponManager::CreateP90()
{
	GamerProfile* profile;
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		profile = &Game::GetInstance()->GetTutorialProfile();
	else
	{
		if (GameplayState::GetInstance()->GetGameMode() == true)
			profile = &Game::GetInstance()->GetStoryProfile();
		else
			profile = &Game::GetInstance()->GetSurvivalProfile();
	}

	P90 * p90 = new P90(GetOwner());  

	p90->SetObtained(profile->p90.isBought);
	
	p90->SetEquipped(false);
	p90->SetGunType(SP90);
	p90->SetType(SMG);
	p90->SetRenderRect(SetImageRect(300, 300, 3, 0));
	p90->SetMagSize(profile->p90.magSize.upgradedSkill.stat);
	p90->SetCurrAmmo(profile->p90.magSize.upgradedSkill.stat);
	p90->SetTotalAmmo(profile->p90.totalAmmo.upgradedSkill.stat);
	p90->SetDamage(profile->p90.damage.upgradedSkill.stat);
	p90->SetBulletSpread(profile->p90.bulletSpread.upgradedSkill.stat);
	p90->SetAmmoCap(profile->p90.ammoCap.upgradedSkill.stat);
	p90->SetReloadTime(profile->p90.reloadTime.upgradedSkill.stat);
	p90->SetAutomatic(true);

	return p90;
}
Weapon * WeaponManager::CreateTech9()
{
	GamerProfile* profile;
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		profile = &Game::GetInstance()->GetTutorialProfile();
	else
	{
		if (GameplayState::GetInstance()->GetGameMode() == true)
			profile = &Game::GetInstance()->GetStoryProfile();
		else
			profile = &Game::GetInstance()->GetSurvivalProfile();
	}

	Tech9 * tech9 = new Tech9(GetOwner());

	tech9->SetObtained(profile->tech9.isBought);
	
	tech9->SetEquipped(false);
	tech9->SetAutomatic(true);

	tech9->SetGunType(TECH9);
	tech9->SetType(SMG);
	tech9->SetRenderRect(SetImageRect(300, 300, 0, 1));
	tech9->SetMagSize(profile->tech9.magSize.upgradedSkill.stat);
	tech9->SetCurrAmmo(profile->tech9.magSize.upgradedSkill.stat);
	tech9->SetTotalAmmo(profile->tech9.totalAmmo.upgradedSkill.stat);
	tech9->SetDamage(profile->tech9.damage.upgradedSkill.stat);
	tech9->SetBulletSpread(profile->tech9.bulletSpread.upgradedSkill.stat);
	tech9->SetAmmoCap(profile->tech9.ammoCap.upgradedSkill.stat);
	tech9->SetReloadTime(profile->tech9.reloadTime.upgradedSkill.stat);
	return tech9;
}
Weapon * WeaponManager::CreateMac10()
{
	GamerProfile* profile;
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		profile = &Game::GetInstance()->GetTutorialProfile();
	else
	{
		if (GameplayState::GetInstance()->GetGameMode() == true)
			profile = &Game::GetInstance()->GetStoryProfile();
		else
			profile = &Game::GetInstance()->GetSurvivalProfile();
	}

	UZI * mac10 = new UZI(GetOwner());

	mac10->SetObtained(profile->mac10.isBought);
	mac10->SetEquipped(false);
	mac10->SetAutomatic(true);

	mac10->SetGunType(MAC10);
	mac10->SetType(SMG);
	mac10->SetRenderRect(SetImageRect(300, 300, 0, 1));
	mac10->SetMagSize(profile->mac10.magSize.upgradedSkill.stat);
	mac10->SetCurrAmmo(profile->mac10.magSize.upgradedSkill.stat);
	mac10->SetTotalAmmo(profile->mac10.totalAmmo.upgradedSkill.stat);
	mac10->SetDamage(profile->mac10.damage.upgradedSkill.stat);
	mac10->SetBulletSpread(profile->mac10.bulletSpread.upgradedSkill.stat);
	mac10->SetAmmoCap(profile->mac10.ammoCap.upgradedSkill.stat);
	mac10->SetReloadTime(profile->mac10.reloadTime.upgradedSkill.stat);
	mac10->SetRecoilTime(.2f);

	return mac10;
}


SGD::Rectangle WeaponManager::SetImageRect(float width, float height, unsigned int row, unsigned int col)
{
	float left = width * col;
	float top = height * row;

	return SGD::Rectangle(left, top, left + width, top + height);
}
