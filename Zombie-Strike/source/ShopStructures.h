#pragma once

#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_Handle.h"
#include <string>



struct UpgradeF
{
	float stat = 0.0f;
	int currTier = 0;
	int maxTier = 0;
};
struct UpgradeN
{
	int stat = 0;
	int currTier = 0;
	int maxTier = 0;
};

struct ButtonF
{
	SGD::Rectangle collisionRect;
	SGD::Point position;
	SGD::HTexture* buttonImage = nullptr;
	UpgradeF upgradedSkill;
	std::string text;
	bool isMaxed;

};
struct ButtonN
{
	SGD::Rectangle collisionRect;
	SGD::Point position;
	SGD::HTexture* buttonImage = nullptr;
	UpgradeN upgradedSkill;
	std::string text; 
	bool isMaxed;

};

struct PistolUpgrade
{
	ButtonN magSize;
	ButtonF reloadTime;
	ButtonF recoilTime;
	bool isEquipt;


};
struct RevolverUpgrade
{
	
	ButtonN totalAmmo;

	ButtonN magSize;
	ButtonN ammoCap;
	ButtonF recoilTime;
	ButtonF reloadTime;
	ButtonN penPower;
	ButtonF damage;
	bool isEquipt;
	bool isBought;

};
struct SMGUpgrade
{
	ButtonN totalAmmo;

	ButtonN magSize;
	ButtonN ammoCap;
	ButtonF reloadTime;
	ButtonF bulletSpread;
	ButtonF damage;
	bool isBought;
	bool isEquipt;

};

struct AssualtRifleUpgrade
{
	ButtonN totalAmmo;

	ButtonN magSize;
	ButtonN ammoCap;
	ButtonF reloadTime;
	ButtonF bulletSpread;
	ButtonF damage;
	ButtonF recoilTime;
	bool isBought;
	bool isEquipt;

};

struct SawnOffUpgrade
{
	ButtonN totalAmmo;

	ButtonN ammoCap;
	ButtonF reloadTime;
	ButtonF bulletSpread;
	ButtonF damage;
	ButtonF recoilTime;
	bool isBought;
	bool isEquipt;




};
struct StdShotgunUpgrade
{
	ButtonN totalAmmo;

	ButtonN magSize;
	ButtonN ammoCap;
	ButtonF reloadTime;
	ButtonF bulletSpread;
	ButtonF damage;
	ButtonF recoilTime;
	bool isBought;
	bool isEquipt;



};

struct SniperUpgrade
{
	ButtonN totalAmmo;

	ButtonN magSize;
	ButtonN penPower;
	


	ButtonN ammoCap;
	ButtonF reloadTime;

	ButtonF bulletSpread;
	ButtonF damage;
	ButtonF recoilTime;

	bool isBought;
	bool isEquipt;




};
struct FlamethrowerUpgrade
{
	ButtonN totalAmmo;

	ButtonN magSize;
	ButtonN ammoCap;
	ButtonF reloadTime;
	ButtonF bulletSpread;
	ButtonF damage;
	ButtonF bulletVelocity;
	bool isBought;
	bool isEquipt;

};
struct GrenadeLauncherUpgrade
{
	ButtonN totalAmmo;

	ButtonN magSize;
	ButtonN ammoCap;
	ButtonF reloadTime;
	ButtonF damage;
	ButtonF bulletVelocity;
	bool isBought;
	bool isEquipt;

};

struct DefenseUpgrade
{

	ButtonF maxHealth;
	ButtonF damage;

	bool isBought;
};

//pFont->Draw("P90: ", { screenSize.width *.1f, screenSize.height * 0.3f }, 1.0f, { 255, 255, 0, 0 });
//pFont->Draw(p90MagLevel.c_str(), { screenSize.width *.1f, Buttons[0].top }, 0.5f, { 255, 255, 0, 0 });
//pFont->Draw("Magezine Size: ", { screenSize.width * 0.3f, Buttons[0].top }, 0.5f, { 255, 255, 0, 0 });
//pFont->Draw(p90ReloadLevel.c_str(), { screenSize.width *.1f, Buttons[1].top }, 0.5f, { 255, 255, 0, 0 });
//pFont->Draw("Reload Speed: ", { screenSize.width * 0.3f, Buttons[1].top }, 0.5f, { 255, 255, 0, 0 });
//pFont->Draw(p90BullSpreadLevel.c_str(), { screenSize.width *.1f, Buttons[2].top }, 0.5, { 255, 255, 0, 0 });
//pFont->Draw("Stability: ", { screenSize.width * 0.3f, Buttons[2].top }, 0.5f, { 255, 255, 0, 0 });
//pFont->Draw(p90DamageLevel.c_str(), { screenSize.width *.1f, Buttons[3].top }, 0.5f, { 255, 255, 0, 0 });
//pFont->Draw("Damage: ", { screenSize.width * 0.3f, Buttons[3].top }, 0.5f, { 255, 255, 0, 0 });
//pFont->Draw(p90AmmoCapLevel.c_str(), { screenSize.width *.1f, Buttons[4].top }, 0.5f, { 255, 255, 0, 0 });
//pFont->Draw("Ammo Capacity: ", { screenSize.width * 0.3f, Buttons[4].top }, 0.5f, { 255, 255, 0, 0 });
//pFont->Draw("Ammo: ", { screenSize.width *.1f, Buttons[5].top }, 0.5f, { 255, 255, 0, 0 });
//pGraphics->DrawTextureSection(weaponsImage, { screenSize.width * .70f, screenSize.height * 0.45f }, SGD::Rectangle(SGD::Point(315.0f, 130.0f), SGD::Size(240.0f, 90.0f)));