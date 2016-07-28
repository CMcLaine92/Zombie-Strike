#pragma once
#include "IGameState.h"
#include "ShopStructures.h"
#include "GamerProfile.h"
#include "Timer.h"
#include <vector>

#define BUTTON_WIDTH 123.0f
#define BUTTON_HEIGHT 27.0f

class BarbedWire;
class LandMine;
class SandBag;

class ShopState : public IGameState
{	
	
	ShopState() = default;
	virtual ~ShopState() = default;

	ShopState(const ShopState&) = delete;
	ShopState& operator=(const ShopState&) = delete;

	int m_nCursor = 0;
	unsigned int equipIndex = 0;
	//Shop time between waves
	Timer m_tShopTimer;

	bool m_bTimerSet = false;
	int barbedWireRepairCost;
	int sandBagRepairCost;
	int landMineRepairCost;


public:
	enum Pages { PISTOLS, SHOTGUNS, SMGS, ASSAULT_RIFLES, HEAVY, DEFENSE };
	enum Gun { GLOCK, REVOLVER, SAWN, PUMP, AUTO, MAC10, TECH9, SP90, M16, LIGHT_MG, AK47, SNIPER, FTHROWER, GLAUNCHER};

	static ShopState* GetInstance(void);

	virtual void	Enter(void)				override;
	virtual void	Exit(void)				override;

	virtual bool	Input(void)				override;
	virtual void	Update(float elapsedTime)	override;
	virtual void	Render(void)				override;

	Timer GetShopTimer() const { return m_tShopTimer; }
	void LoadShopStatus();
	void SaveProfile();
	void UpdateProfile();
	void UpdateWeaponManager();


	void ControllerSelectionCheck(void);	// select with Dpad
	void DPadWeaponResults(void);			//		-Dpad: weapons
	void DPadDefenceResults(void);			//		-Dpad: defences

	void JoystickWeaponResults(void);			//		-Dpad: weapons
	void JoystickDefenceResults(void);			//		-Dpad: defences


	void DrawControllerInput(void);			// controller input render
	void DrawKeyboardInput(void);			// keyboard input render


private:
	PistolUpgrade pistolUpgrade;
	RevolverUpgrade revolverUpgrade;
	SMGUpgrade uziUpgrade;
	SMGUpgrade tech9Upgrade;
	SMGUpgrade p90Upgrade;
	AssualtRifleUpgrade ak47Upgrade;
	AssualtRifleUpgrade m16Upgrade;
	AssualtRifleUpgrade lmgUpgrade;
	SawnOffUpgrade sawnOffUpgrade;
	StdShotgunUpgrade pumpShotgunUpgrade;
	StdShotgunUpgrade autoShotgunUpgrade;
	SniperUpgrade sniperUpgrade;
	FlamethrowerUpgrade flameUpgrade;
	GrenadeLauncherUpgrade nadeLauncherUpgrade;
	DefenseUpgrade barbedwire;
	DefenseUpgrade sandBag;
	DefenseUpgrade landMine;

	

	SGD::Rectangle shotTab1 = { 350, 100, 350 + BUTTON_WIDTH, 127 };
	SGD::Rectangle shotTab2 = { shotTab1.right, 100, shotTab1.right + BUTTON_WIDTH, 127 };
	SGD::Rectangle shotTab3 = { shotTab2.right, 100, shotTab2.right + BUTTON_WIDTH, 127 };

	float numLandMines = 0;
	float sandBagCurrHealth = 0;
	float sandBagMaxHealth = 0;
	float barbWireCurrHealth = 0;
	float barbWireMaxHealth = 0;

	int currPage = 0;
	int currTab = 0;

	SGD::Point mousePos;
	SGD::HTexture weaponsImage = SGD::INVALID_HANDLE;
	SGD::HTexture buyButton = SGD::INVALID_HANDLE;
	SGD::HTexture upgradeButton = SGD::INVALID_HANDLE;
	SGD::HTexture m_hReticleImage = SGD::INVALID_HANDLE;
	SGD::HTexture m_hBackground = SGD::INVALID_HANDLE;


	GamerProfile profile;
	SGD::Rectangle Buttons[9];
	SGD::Rectangle DefenseButtons[8];

	SGD::Size screenSize;

	std::vector<BarbedWire*> barbedWires;
	std::vector<SandBag*> sandBags;
	std::vector<LandMine*> landMines;






	int numoptions = 0;
	int buttonnum = 0;

	bool isJSmoved = false;
};

