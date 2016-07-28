#pragma once
#include <string>
#include <vector>
#include "ShopStructures.h"
#include <ctime> 
#include <cwchar>

struct GamerProfile
{
	//float MaxEnergy = 100.0f;
	//float MaxStamina = 100.0f;
	//float CamoMultiplier = 1.0f;
	//float SpeedMultiplier = 1.0f;
	//float RadarMultiplier = 1.0f;
	//int LevelsComplete = 0;
	std::string path;
	//bool m_bHasKey = false;
	//bool CheckPointReached = false;
	PistolUpgrade pistol;
	RevolverUpgrade revolver;
	SMGUpgrade mac10;
	SMGUpgrade tech9;
	SMGUpgrade p90;
	SawnOffUpgrade sawnoff;
	StdShotgunUpgrade pumpShotgun;
	StdShotgunUpgrade autoShotgun;
	AssualtRifleUpgrade ak47;
	AssualtRifleUpgrade m16;
	AssualtRifleUpgrade lmg;
	SniperUpgrade sniper;
	FlamethrowerUpgrade flameThrower;
	GrenadeLauncherUpgrade nadeLauncher;
	DefenseUpgrade barbWire;
	DefenseUpgrade sandBag;
	DefenseUpgrade landMine;
	tm time;
	

	int money;
	int numTurrets;
	int maxNumTurrets;
	float health;
	
	bool sandBagStates[66];
	bool landMineStates[55];
	bool barbWireStates[74];

	int wavesComplete;



};