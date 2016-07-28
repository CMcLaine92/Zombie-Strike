#pragma once
#include "Weapon.h"
#include "../SGD Wrappers/SGD_Declarations.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include <vector>

class Player;

using namespace std;

class WeaponManager : public Weapon
{   

	vector<Weapon*> m_vWeapons;

	//Weapon * m_aWpnInventory[5];

	int curIndex;
	int equipIndex = 0;
	
	//Image Assets
	SGD::HTexture m_hHudWpn = SGD::INVALID_HANDLE;

		//Sound Assets
	SGD::HAudio m_hWpnSwitch = SGD::INVALID_HANDLE;
	
public:

	WeaponManager() = default;
	virtual ~WeaponManager() = default;

	static WeaponManager* GetInstance(void);

	////Accessors////
	//Returns weapon vector
	vector<Weapon*> GetWeapons() { return m_vWeapons; }

	//Returns currently selected weapon
	Weapon * GetSelected() { return m_vWeapons[curIndex]; }

	SGD::HTexture GetWeaponImage() { return m_hHudWpn; }

	////Mutators////
	//Sets currently selected weapon
	void SelectWeapon(int type);
	void SetCurrIndex(int index) { curIndex = index; }
	

	//Adds weapons to weapon vector
	void AddWeapons(Weapon*);

	void SetPistolImage(SGD::HTexture hWpn) { m_hHudWpn = hWpn; }

	void Initialize(MovingObject& owner);
	void Render();
	void Input();
	void Update(float dt);
	void Exit();

	SGD::Rectangle SetImageRect(float width,  float height, unsigned int row, unsigned int col);

	//Weapon factory methods
	Weapon * CreatePistol();
	Weapon* CreateRevolver();
	Weapon * CreateMac10();
	Weapon * CreateTech9();
	Weapon * CreateP90();
	Weapon * CreateAssaultRifle();
	Weapon * CreateAK47();
	Weapon * CreateLMG();
	Weapon* CreateSawnOff();
	Weapon * CreatePumpShotgun();
	Weapon* CreateAutoShotgun();
	Weapon * CreateSniper();
	Weapon * CreateFlameThrower();
	Weapon* CreateGrenadeLauncher();



};

