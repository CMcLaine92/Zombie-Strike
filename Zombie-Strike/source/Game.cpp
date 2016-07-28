#include "Game.h"

#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"
#include "../SGD Wrappers/SGD_EventManager.h"
#include "AnimationManager.h"
#include "WeaponManager.h"

#include "BitmapFont.h"
#include "IGameState.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "LoseGameState.h"

#include <ctime>
#include <cstdlib>
#include <cassert>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlobj.h>
#include <fstream>


/**************************************************************/
// Singleton
//	- instantiate the static member
/*static*/ Game* Game::s_pInstance = nullptr;

// GetInstance
//	- allocate the ONE instance & return it
/*static*/ Game* Game::GetInstance( void )
{
	if( s_pInstance == nullptr )
		s_pInstance = new Game;

	return s_pInstance;
}

// DeleteInstance
//	- deallocate the ONE instance
/*static*/ void Game::DeleteInstance( void )
{
	delete s_pInstance;
	s_pInstance = nullptr;
}


/**************************************************************/
// Initialize
//	- initialize the SGD wrappers
//	- enter the Main Menu state
bool Game::Initialize( float width, float height, const wchar_t* title )
{
	
	// Seed First!
	srand( (unsigned int)time( nullptr ) );
	rand();

	ShowCursor(false);

	// Initialize the wrappers
	if( SGD::AudioManager::GetInstance()->Initialize() == false 
		|| SGD::GraphicsManager::GetInstance()->Initialize( false ) == false
		|| SGD::InputManager::GetInstance()->Initialize() == false )
		return false;

	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	// Store the size parameters
	m_fScreenWidth	= width;
	m_fScreenHeight = height;


	// Store the title parameter
	m_strGameTitle = title;


	// Allocate & initialize the font
	m_pFont = new BitmapFont;
	m_pFont2 = new BitmapFont;

	m_pFont->Initialize("resource/bitmapfonts/Remains.xml", '\0', false);
	m_pFont2->Initialize("resource/bitmapfonts/Arial.xml", '\0', false);


	AnimationManager*		pAnimationManager = AnimationManager::GetInstance();

	// player animations
	pAnimationManager->Load("resource/config/animations/PlayerAnimation.xml", "player");
	pAnimationManager->Load("resource/config/animations/FlameThrower.xml", "flameThrowerRound");
	pAnimationManager->Load("resource/config/animations/testLandMine.xml", "testLandmine");
	pAnimationManager->Load("resource/config/animations/barbwireAnimation.xml", "testBarbwire");
	pAnimationManager->Load("resource/config/animations/sandbagAnimation.xml", "testSandbag");

	pAnimationManager->Load("resource/config/animations/Bullet.xml", "bullet");
	pAnimationManager->Load("resource/config/animations/Player_Death2.xml", "playerDeath");
	pAnimationManager->Load("resource/config/animations/bloodExplosion.xml", "bloodExplosion");

	pAnimationManager->Load("resource/config/animations/Landmine_Animation.xml", "landmine");
	pAnimationManager->Load("resource/config/animations/Sandbag_Animation.xml", "sandbag");
	pAnimationManager->Load("resource/config/animations/Barbedwire_Animation.xml", "barbedwire");


	// Weapons
	pAnimationManager->Load("resource/config/animations/Pistol_Idle_Animation.xml",		"pistolIdle");
	pAnimationManager->Load("resource/config/animations/Pistol_Walk_Animation.xml",		"pistolWalk");
	pAnimationManager->Load("resource/config/animations/Pistol_Run_Animation.xml",		"pistolRun");

	pAnimationManager->Load("resource/config/animations/Shotgun_Idle_Animation.xml",	"shotgunIdle");
	pAnimationManager->Load("resource/config/animations/Shotgun_Walk_Animation.xml",	"shotgunWalk");
	pAnimationManager->Load("resource/config/animations/Shotgun_Run_Animation.xml",		"shotgunRun");
	pAnimationManager->Load("resource/config/animations/Sawnoff_Idle_Animation.xml",	"sawnoffIdle");
	pAnimationManager->Load("resource/config/animations/Sawnoff_Walk_Animation.xml",	"sawnoffWalk");
	pAnimationManager->Load("resource/config/animations/Sawnoff_Run_Animation.xml",		"sawnoffRun");

	pAnimationManager->Load("resource/config/animations/Rifle_Idle_Animation.xml",		"rifleIdle");
	pAnimationManager->Load("resource/config/animations/Rifle_Walk_Animation.xml",		"rifleWalk");
	pAnimationManager->Load("resource/config/animations/Rifle_Run_Animation.xml",		"rifleRun");

	pAnimationManager->Load("resource/config/animations/Sniper_Idle_Animation.xml",		"sniperIdle");
	pAnimationManager->Load("resource/config/animations/Sniper_Walk_Animation.xml",		"sniperWalk");
	pAnimationManager->Load("resource/config/animations/Sniper_Run_Animation.xml",		"sniperRun");

	pAnimationManager->Load("resource/config/animations/Flamethrower_Idle_Animation.xml",	"flamethrowerIdle");
	pAnimationManager->Load("resource/config/animations/Flamethrower_Walk_Animation.xml",	"flamethrowerWalk");
	pAnimationManager->Load("resource/config/animations/Flamethrower_Run_Animation.xml",	"flamethrowerRun");
	pAnimationManager->Load("resource/config/animations/Heavy_Idle_Animation.xml",			"heavyIdle");
	pAnimationManager->Load("resource/config/animations/Heavy_Walk_Animation.xml",			"heavyWalk");
	pAnimationManager->Load("resource/config/animations/Heavy_Run_Animation.xml",			"heavyRun");


	// enemy animations
	pAnimationManager->Load("resource/config/animations/ZombieWalker_Animation.xml", "slowZombie");
	pAnimationManager->Load("resource/config/animations/ZombieRunner_Animation.xml", "fastZombie");
	pAnimationManager->Load("resource/config/animations/ZombieTank_Animation.xml", "tankZombie");
	pAnimationManager->Load("resource/config/animations/ZombieSploder_Animation.xml", "explodingZombie");
	pAnimationManager->Load("resource/config/animations/Explosion_Animation1.xml", "explosion");
	pAnimationManager->Load("resource/config/animations/ZombieFat_Animation.xml", "fatZombie");

	pAnimationManager->Load("resource/config/animations/AcidAnimation.xml", "puke");

	pAnimationManager->Load("resource/config/animations/ZombieWalker_Death1.xml", "slowZombieDeath");
	pAnimationManager->Load("resource/config/animations/ZombieRunner_Death1.xml", "fastZombieDeath");
	pAnimationManager->Load("resource/config/animations/ZombieSploder_Death1.xml", "explodingZombieDeath");
	pAnimationManager->Load("resource/config/animations/ZombieTank_Death1.xml", "tankZombieDeath");
	pAnimationManager->Load("resource/config/animations/ZombieFat_Death1.xml", "fatZombieDeath");

	//Blood Animation
	pAnimationManager->Load("resource/config/animations/BloodAnimations/blood1.xml", "blood1");
	pAnimationManager->Load("resource/config/animations/BloodAnimations/blood2.xml", "blood2");
	pAnimationManager->Load("resource/config/animations/BloodAnimations/blood3.xml", "blood3");
	pAnimationManager->Load("resource/config/animations/BloodAnimations/blood4.xml", "blood4");

	// other animations
	pAnimationManager->Load("resource/config/animations/Turret_Animation2.xml", "turret");
	pAnimationManager->Load("resource/config/animations/House_Animation.xml", "house");



	m_hHudWpn = pGraphics->LoadTexture("resource/graphics/Weapons/hudweapons.png");
	m_hReticleImage = pGraphics->LoadTexture("resource/graphics/Weapons/crosshair.png");

	// Load assets
	storyMusic = pAudio->LoadAudio("resource/audio/AmbienceDrama.xwm");

	turret_good			= SGD::AudioManager::GetInstance()->LoadAudio("resource/audio/turret_good.wav");
	turret_bad			= SGD::AudioManager::GetInstance()->LoadAudio("resource/audio/turret_bad.wav");

	m_hMainTheme = pAudio->LoadAudio("resource/audio/zstrikemain.xwm");
	m_hSurvivalTheme = pAudio->LoadAudio("resource/audio/zstrikesurvival.xwm");

	// SFX
	m_hWaveChange		= pAudio->LoadAudio("resource/audio/wavechange.wav");
	m_hWpnSwitch		= pAudio->LoadAudio("resource/audio/switchweapon.wav");
	playerDeath			= pAudio->LoadAudio("resource/audio/player_death1.wav");
	playerHurt1			= pAudio->LoadAudio("resource/audio/player_grunt1.wav");
	playerHurt2			= pAudio->LoadAudio("resource/audio/player_grunt2.wav");
	playerHurt3			= pAudio->LoadAudio("resource/audio/player_grunt3.wav");
	cannot_use_skill	= pAudio->LoadAudio("resource/audio/cannotUseAbility7.wav");
	footstep			= pAudio->LoadAudio("resource/audio/FootstepsWood.wav");
	zombie_pain			= pAudio->LoadAudio("resource/audio/zombie_howl.wav");
	bullet_hit_zombie	= pAudio->LoadAudio("resource/audio/bullet_hit_zombie.wav");
	bullet_hit_house	= pAudio->LoadAudio("resource/audio/bullet_hit_house.wav");
	out_of_ammo			= pAudio->LoadAudio("resource/audio/out_of_ammo.wav");
	reload_begin		= pAudio->LoadAudio("resource/audio/reload_begin.wav");
	reload_finish		= pAudio->LoadAudio("resource/audio/reload_finish.wav");
	explosion			= pAudio->LoadAudio("resource/audio/Splode2.wav");
	vomit_hit_player	= pAudio->LoadAudio("resource/audio/splat.wav");
	pistol_fire			= pAudio->LoadAudio("resource/audio/pistol_fire.wav");
	shotgun_fire		= pAudio->LoadAudio("resource/audio/shotgun_fire.wav");
	rifle_fire			= pAudio->LoadAudio("resource/audio/rifle_fire.wav");
	sniper_fire			= pAudio->LoadAudio("resource/audio/sniper_fire.wav");
	flamethrower_fire	= pAudio->LoadAudio("resource/audio/fire_ignite_1.wav");
	smg_fire			= pAudio->LoadAudio("resource/audio/smg_fire_1.wav");
	rpg_fire			= pAudio->LoadAudio("resource/audio/RocketLauncher.wav");
	vomit_fire			= pAudio->LoadAudio("resource/audio/vomit.wav");
	zombie_hit_house1 = pAudio->LoadAudio("resource/audio/zombie_hit_house1.wav");
	zombie_hit_house2 = pAudio->LoadAudio("resource/audio/zombie_hit_house2.wav");


	// Setup the profiles
	CreateStoryProfiles();
	CreateSurvivalProfiles();
	CreateTutorialProfile();

	LoadStoryProfiles();
	LoadSurvivalProfiles();
	LoadTutorialProfiles();
	

	// Start the game in the Main Menu state
	/*
	m_pCurrState = MainMenuState::GetInstance();
	m_pCurrState->Enter();
	stateMachine.push(m_pCurrState);
	*/
	Game::GetInstance()->AddState(MainMenuState::GetInstance());


	// Store the current time (in milliseconds)
	m_ulGameTime	= GetTickCount();


	return true;	// success!
}


/**************************************************************/
// Main
//	- update the SGD wrappers
//	- run the current state
int Game::Update( void )
{
	// Update the wrappers
	if( SGD::AudioManager::GetInstance()->Update() == false 
		|| SGD::GraphicsManager::GetInstance()->Update() == false
		|| SGD::InputManager::GetInstance()->Update() == false )
		return -10;		// exit FAILURE!

	
	// Calculate the elapsed time between frames
	unsigned long now = GetTickCount();					// current time in milliseconds
	elapsedTime = (now - m_ulGameTime) / 1000.0f;		// convert to fraction of a second
	m_ulGameTime = now;									// store the current time

	// Cap the elapsed time to 1/8th of a second
	if( elapsedTime > 0.125f )
		elapsedTime = 0.125f;


	/**********************************************************/
	// 'Alt + Enter' -> Full screen
	/**********************************************************/

	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	pInput->IsControllerConnected(0);

	// Let the current state handle input

	m_pCurrState = stateMachine.top();
	if (isActive == true)
	{
		if (m_pCurrState->Input() == false)
			return 1;	// exit success!
	}



	// Update & render the current state if it was not changed
	if (m_pCurrState == stateMachine.top())
	{
	
		if (m_pCurrState != nullptr)
			m_pCurrState->Update(elapsedTime);

		if (m_pCurrState != nullptr)
			m_pCurrState->Render();
	}


	return 0;		// keep playing!
}


/**************************************************************/
// Terminate
//	- exit the current state
//	- terminate the SGD wrappers
void Game::Terminate( void )
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	// Terminate & deallocate the font
	m_pFont->Terminate();
	delete m_pFont;
	m_pFont = nullptr;

	m_pFont2->Terminate();
	delete m_pFont2;
	m_pFont2 = nullptr;

	pGraphics->UnloadTexture(m_hHudWpn);
	pAudio->UnloadAudio(m_hWpnSwitch);

	pAudio->UnloadAudio(turret_good);
	pAudio->UnloadAudio(turret_bad);


	// Exit the current state
	
	while (stateMachine.empty() == false)
		Game::GetInstance()->RemoveState();

	// Unload assets
	pGraphics->UnloadTexture(loadScreen);
	pGraphics->UnloadTexture(m_hReticleImage);

	pAudio->UnloadAudio(m_hMainTheme);
	pAudio->UnloadAudio(m_hSurvivalTheme);

	pAudio->UnloadAudio(storyMusic);
	pGraphics->UnloadTexture(m_hHudWpn);
	pAudio->UnloadAudio(playerDeath);
	pAudio->UnloadAudio(playerHurt1);
	pAudio->UnloadAudio(playerHurt2);
	pAudio->UnloadAudio(playerHurt3);
	pAudio->UnloadAudio(cannot_use_skill);
	pAudio->UnloadAudio(footstep);
	pAudio->UnloadAudio(m_hWpnSwitch);
	pAudio->UnloadAudio(zombie_pain);
	pAudio->UnloadAudio(bullet_hit_zombie);
	pAudio->UnloadAudio(bullet_hit_house);
	pAudio->UnloadAudio(out_of_ammo);
	pAudio->UnloadAudio(reload_begin);
	pAudio->UnloadAudio(reload_finish);
	pAudio->UnloadAudio(explosion);
	pAudio->UnloadAudio(m_hWaveChange);
	pAudio->UnloadAudio(vomit_hit_player);

	pAudio->UnloadAudio(pistol_fire);
	pAudio->UnloadAudio(shotgun_fire);
	pAudio->UnloadAudio(rifle_fire);
	pAudio->UnloadAudio(sniper_fire);
	pAudio->UnloadAudio(flamethrower_fire);
	pAudio->UnloadAudio(smg_fire);
	pAudio->UnloadAudio(rpg_fire);
	pAudio->UnloadAudio(vomit_fire);
	pAudio->UnloadAudio(zombie_hit_house1);
	pAudio->UnloadAudio(zombie_hit_house2);


	AnimationManager::GetInstance()->Shutdown();

	// Terminate the core SGD wrappers
	SGD::AudioManager::GetInstance()->Terminate();
	SGD::AudioManager::DeleteInstance();

	SGD::GraphicsManager::GetInstance()->Terminate();
	SGD::GraphicsManager::DeleteInstance();

	SGD::InputManager::GetInstance()->Terminate();
	SGD::InputManager::DeleteInstance();
	
}


/**************************************************************/
// AddState
//	- enter the new state to allocate resources
void Game::AddState( IGameState* pNewState )
{
	// Enter the new state
	m_pCurrState = pNewState;
	m_pCurrState->Enter();
	

	// Store the new state
	stateMachine.push(m_pCurrState);
}


/**************************************************************/
// RemoveState
//	- exit the current state to release resources
void Game::RemoveState( void )
{
	// Exit the old state
	m_pCurrState = stateMachine.top();
	if (m_pCurrState != nullptr)
		m_pCurrState->Exit();
	m_pCurrState = nullptr;

	m_pCurrState = nullptr;

	stateMachine.pop();
}


/**************************************************************/
// LoadProfiles
void Game::LoadStoryProfiles( void )
{
	//* If using Wide characters under project settings *//
	HRESULT hr;
	ostringstream stringstream;
	char path[MAX_PATH];
	LPWSTR wszPath = NULL;
	size_t   size;


	// Get the path to the app data folder
	hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, 0, &wszPath);


	// Convert from LPWSTR to char[]
	wcstombs_s(&size, path, MAX_PATH, wszPath, MAX_PATH);


	// Convert char types
	if (hr == S_OK)
		stringstream << path;
	string pathtowrite = stringstream.str();


	// Add the company and game information
	pathtowrite += "\\CTS\\ZombieStrike\\Story\\";


	// Create our directory
	SHCreateDirectoryEx(NULL, pathtowrite.c_str(), 0);


	// Create our save file
	for (unsigned int i = 1; i < 4; i++)
	{
		string filePath = pathtowrite;

		filePath += "savefile.save";
		filePath += std::to_string(i);

		ifstream fin(filePath.c_str());
		if (fin.is_open())
		{
			getline(fin, storyProfiles[i - 1].path);

			fin >> storyProfiles[i - 1].time.tm_year;

			fin >> storyProfiles[i - 1].time.tm_mon;
			fin >> storyProfiles[i - 1].time.tm_mday;
			fin >> storyProfiles[i - 1].time.tm_hour;
			fin >> storyProfiles[i - 1].time.tm_min;
			fin >> storyProfiles[i - 1].time.tm_sec;

			fin >> storyProfiles[i - 1].health;

#pragma region Pistols

			//pistol
			fin >> storyProfiles[i - 1].pistol.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].pistol.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].pistol.magSize.upgradedSkill.maxTier;

		
			fin >> storyProfiles[i - 1].pistol.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].pistol.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].pistol.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].pistol.recoilTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].pistol.recoilTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].pistol.recoilTime.upgradedSkill.maxTier;
			fin >> storyProfiles[i - 1].pistol.isEquipt;

			//revolver
			fin >> storyProfiles[i - 1].revolver.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].revolver.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].revolver.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].revolver.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].revolver.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].revolver.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].revolver.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].revolver.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].revolver.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].revolver.recoilTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].revolver.recoilTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].revolver.recoilTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].revolver.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].revolver.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].revolver.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].revolver.penPower.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].revolver.penPower.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].revolver.penPower.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].revolver.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].revolver.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].revolver.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].revolver.isBought;
			fin >> storyProfiles[i - 1].revolver.isEquipt;



#pragma endregion





#pragma region SMGs
			//Mac10
			fin >> storyProfiles[i - 1].mac10.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].mac10.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].mac10.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].mac10.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].mac10.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].mac10.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].mac10.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].mac10.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].mac10.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].mac10.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].mac10.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].mac10.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].mac10.bulletSpread.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].mac10.bulletSpread.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].mac10.bulletSpread.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].mac10.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].mac10.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].mac10.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].mac10.isBought;
			fin >> storyProfiles[i - 1].mac10.isEquipt;

			//Tech9
			fin >> storyProfiles[i - 1].tech9.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].tech9.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].tech9.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].tech9.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].tech9.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].tech9.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].tech9.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].tech9.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].tech9.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].tech9.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].tech9.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].tech9.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].tech9.bulletSpread.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].tech9.bulletSpread.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].tech9.bulletSpread.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].tech9.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].tech9.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].tech9.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].tech9.isBought;
			fin >> storyProfiles[i - 1].tech9.isEquipt;

			//P90
			fin >> storyProfiles[i - 1].p90.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].p90.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].p90.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].p90.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].p90.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].p90.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].p90.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].p90.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].p90.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].p90.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].p90.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].p90.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].p90.bulletSpread.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].p90.bulletSpread.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].p90.bulletSpread.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].p90.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].p90.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].p90.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].p90.isBought;
			fin >> storyProfiles[i - 1].p90.isEquipt;

#pragma endregion

#pragma region Shotguns

			//SawnOff
			fin >> storyProfiles[i - 1].sawnoff.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sawnoff.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sawnoff.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sawnoff.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sawnoff.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sawnoff.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sawnoff.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sawnoff.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sawnoff.reloadTime.upgradedSkill.maxTier;


			fin >> storyProfiles[i - 1].sawnoff.bulletSpread.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sawnoff.bulletSpread.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sawnoff.bulletSpread.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sawnoff.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sawnoff.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sawnoff.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sawnoff.recoilTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sawnoff.recoilTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sawnoff.recoilTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sawnoff.isBought;
			fin >> storyProfiles[i - 1].sawnoff.isEquipt;


			//Pump
			fin >> storyProfiles[i - 1].pumpShotgun.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].pumpShotgun.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].pumpShotgun.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].pumpShotgun.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].pumpShotgun.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].pumpShotgun.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].pumpShotgun.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].pumpShotgun.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].pumpShotgun.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].pumpShotgun.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].pumpShotgun.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].pumpShotgun.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].pumpShotgun.bulletSpread.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].pumpShotgun.bulletSpread.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].pumpShotgun.bulletSpread.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].pumpShotgun.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].pumpShotgun.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].pumpShotgun.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].pumpShotgun.recoilTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].pumpShotgun.recoilTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].pumpShotgun.recoilTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].pumpShotgun.isBought;
			fin >> storyProfiles[i - 1].pumpShotgun.isEquipt;

			//Auto
			fin >> storyProfiles[i - 1].autoShotgun.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].autoShotgun.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].autoShotgun.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].autoShotgun.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].autoShotgun.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].autoShotgun.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].autoShotgun.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].autoShotgun.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].autoShotgun.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].autoShotgun.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].autoShotgun.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].autoShotgun.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].autoShotgun.bulletSpread.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].autoShotgun.bulletSpread.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].autoShotgun.bulletSpread.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].autoShotgun.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].autoShotgun.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].autoShotgun.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].autoShotgun.recoilTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].autoShotgun.recoilTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].autoShotgun.recoilTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].autoShotgun.isBought;
			fin >> storyProfiles[i - 1].autoShotgun.isEquipt;



#pragma endregion

#pragma region Assault Rifles

			//AK-47
			fin >> storyProfiles[i - 1].ak47.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].ak47.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].ak47.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].ak47.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].ak47.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].ak47.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].ak47.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].ak47.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].ak47.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].ak47.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].ak47.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].ak47.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].ak47.bulletSpread.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].ak47.bulletSpread.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].ak47.bulletSpread.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].ak47.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].ak47.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].ak47.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].ak47.recoilTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].ak47.recoilTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].ak47.recoilTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].ak47.isBought;
			fin >> storyProfiles[i - 1].ak47.isEquipt;

			//M-16
			fin >> storyProfiles[i - 1].m16.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].m16.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].m16.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].m16.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].m16.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].m16.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].m16.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].m16.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].m16.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].m16.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].m16.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].m16.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].m16.bulletSpread.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].m16.bulletSpread.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].m16.bulletSpread.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].m16.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].m16.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].m16.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].m16.recoilTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].m16.recoilTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].m16.recoilTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].m16.isBought;
			fin >> storyProfiles[i - 1].m16.isEquipt;

			//LMG
			fin >> storyProfiles[i - 1].lmg.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].lmg.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].lmg.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].lmg.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].lmg.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].lmg.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].lmg.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].lmg.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].lmg.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].lmg.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].lmg.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].lmg.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].lmg.bulletSpread.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].lmg.bulletSpread.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].lmg.bulletSpread.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].lmg.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].lmg.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].lmg.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].lmg.recoilTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].lmg.recoilTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].lmg.recoilTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].lmg.isBought;
			fin >> storyProfiles[i - 1].lmg.isEquipt;

#pragma endregion

#pragma region Heavy Weapons

			//Sniper
			fin >> storyProfiles[i - 1].sniper.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sniper.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sniper.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sniper.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sniper.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sniper.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sniper.penPower.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sniper.penPower.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sniper.penPower.upgradedSkill.maxTier;


			fin >> storyProfiles[i - 1].sniper.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sniper.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sniper.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sniper.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sniper.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sniper.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sniper.bulletSpread.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sniper.bulletSpread.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sniper.bulletSpread.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sniper.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sniper.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sniper.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sniper.recoilTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sniper.recoilTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sniper.recoilTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].sniper.isBought;
			fin >> storyProfiles[i - 1].sniper.isEquipt;

			//Flamethrower

			fin >> storyProfiles[i - 1].flameThrower.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].flameThrower.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].flameThrower.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].flameThrower.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].flameThrower.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].flameThrower.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].flameThrower.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].flameThrower.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].flameThrower.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].flameThrower.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].flameThrower.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].flameThrower.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].flameThrower.bulletSpread.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].flameThrower.bulletSpread.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].flameThrower.bulletSpread.upgradedSkill.maxTier;
		
			fin >> storyProfiles[i - 1].flameThrower.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].flameThrower.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].flameThrower.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].flameThrower.bulletVelocity.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].flameThrower.bulletVelocity.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].flameThrower.bulletVelocity.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].flameThrower.isBought;
			fin >> storyProfiles[i - 1].flameThrower.isEquipt;

			//Grenade Launcher

			fin >> storyProfiles[i - 1].nadeLauncher.totalAmmo.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].nadeLauncher.totalAmmo.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].nadeLauncher.totalAmmo.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].nadeLauncher.magSize.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].nadeLauncher.magSize.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].nadeLauncher.magSize.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].nadeLauncher.ammoCap.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].nadeLauncher.ammoCap.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].nadeLauncher.ammoCap.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].nadeLauncher.reloadTime.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].nadeLauncher.reloadTime.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].nadeLauncher.reloadTime.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].nadeLauncher.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].nadeLauncher.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].nadeLauncher.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].nadeLauncher.bulletVelocity.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].nadeLauncher.bulletVelocity.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].nadeLauncher.bulletVelocity.upgradedSkill.maxTier;
		
			fin >> storyProfiles[i - 1].nadeLauncher.isBought;
			fin >> storyProfiles[i - 1].nadeLauncher.isEquipt;

			//Barb Wire
			fin >> storyProfiles[i - 1].barbWire.maxHealth.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].barbWire.maxHealth.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].barbWire.maxHealth.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].barbWire.damage.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].barbWire.damage.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].barbWire.damage.upgradedSkill.maxTier;

			fin >> storyProfiles[i - 1].barbWire.isBought;
			
			for (size_t j = 0; j < 74; j++)
			{
				
				fin >> storyProfiles[i - 1].barbWireStates[j];
				

			}
			//Sandbag

			fin >> storyProfiles[i - 1].sandBag.maxHealth.upgradedSkill.stat;
			fin >> storyProfiles[i - 1].sandBag.maxHealth.upgradedSkill.currTier;
			fin >> storyProfiles[i - 1].sandBag.maxHealth.upgradedSkill.maxTier;


			fin >> storyProfiles[i - 1].sandBag.isBought;

			for (size_t j = 0; j < 66; j++)
			{
				
				fin >> storyProfiles[i - 1].sandBagStates[j];
			

			}
			

			fin >> storyProfiles[i - 1].landMine.isBought;

			for (size_t j = 0; j < 55; j++)
			{
				
				fin >> storyProfiles[i - 1].landMineStates[j];
				

			}

			fin >> storyProfiles[i - 1].numTurrets;

			fin >> storyProfiles[i - 1].maxNumTurrets;


			fin >> storyProfiles[i - 1].wavesComplete;





			//LandMine



#pragma endregion
			
			fin.close();
		}
	}
}

void Game::LoadSurvivalProfiles(void)
{
	//* If using Wide characters under project settings *//
	HRESULT hr;
	ostringstream stringstream;
	char path[MAX_PATH];
	LPWSTR wszPath = NULL;
	size_t   size;


	// Get the path to the app data folder
	hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, 0, &wszPath);


	// Convert from LPWSTR to char[]
	wcstombs_s(&size, path, MAX_PATH, wszPath, MAX_PATH);


	// Convert char types
	if (hr == S_OK)
		stringstream << path;
	string pathtowrite = stringstream.str();


	// Add the company and game information
	pathtowrite += "\\CTS\\ZombieStrike\\Survival\\";


	// Create our directory
	SHCreateDirectoryEx(NULL, pathtowrite.c_str(), 0);


	// Create our save file
	for (unsigned int i = 1; i < 4; i++)
	{
		string filePath = pathtowrite;

		filePath += "savefile.save";
		filePath += std::to_string(i);

		ifstream fin(filePath.c_str());
		if (fin.is_open())
		{
			getline(fin, survivalProfiles[i - 1].path);

			fin >> survivalProfiles[i - 1].time.tm_year;

			fin >> survivalProfiles[i-1].time.tm_mon;
			fin >> survivalProfiles[i - 1].time.tm_mday;
			fin >> survivalProfiles[i - 1].time.tm_hour;
			fin >> survivalProfiles[i - 1].time.tm_min;
			fin >> survivalProfiles[i - 1].time.tm_sec;

			fin >> survivalProfiles[i - 1].health;


#pragma region Pistols

			//pistol
			fin >> survivalProfiles[i - 1].pistol.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].pistol.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].pistol.magSize.upgradedSkill.maxTier;


			fin >> survivalProfiles[i - 1].pistol.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].pistol.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].pistol.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].pistol.recoilTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].pistol.recoilTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].pistol.recoilTime.upgradedSkill.maxTier;
			fin >> survivalProfiles[i - 1].pistol.isEquipt;

			//revolver
			fin >> survivalProfiles[i - 1].revolver.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].revolver.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].revolver.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].revolver.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].revolver.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].revolver.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].revolver.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].revolver.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].revolver.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].revolver.recoilTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].revolver.recoilTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].revolver.recoilTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].revolver.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].revolver.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].revolver.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].revolver.penPower.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].revolver.penPower.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].revolver.penPower.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].revolver.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].revolver.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].revolver.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].revolver.isBought;
			fin >> survivalProfiles[i - 1].revolver.isEquipt;


#pragma endregion





#pragma region SMGs
			//Mac10
			fin >> survivalProfiles[i - 1].mac10.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].mac10.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].mac10.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].mac10.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].mac10.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].mac10.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].mac10.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].mac10.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].mac10.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].mac10.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].mac10.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].mac10.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].mac10.bulletSpread.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].mac10.bulletSpread.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].mac10.bulletSpread.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].mac10.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].mac10.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].mac10.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].mac10.isBought;
			fin >> survivalProfiles[i - 1].mac10.isEquipt;

			//Tech9
			fin >> survivalProfiles[i - 1].tech9.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].tech9.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].tech9.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].tech9.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].tech9.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].tech9.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].tech9.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].tech9.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].tech9.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].tech9.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].tech9.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].tech9.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].tech9.bulletSpread.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].tech9.bulletSpread.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].tech9.bulletSpread.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].tech9.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].tech9.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].tech9.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].tech9.isBought;
			fin >> survivalProfiles[i - 1].tech9.isEquipt;

			//P90
			fin >> survivalProfiles[i - 1].p90.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].p90.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].p90.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].p90.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].p90.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].p90.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].p90.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].p90.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].p90.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].p90.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].p90.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].p90.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].p90.bulletSpread.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].p90.bulletSpread.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].p90.bulletSpread.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].p90.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].p90.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].p90.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].p90.isBought;
			fin >> survivalProfiles[i - 1].p90.isEquipt;

#pragma endregion

#pragma region Shotguns

			//SawnOff
			fin >> survivalProfiles[i - 1].sawnoff.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sawnoff.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sawnoff.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sawnoff.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sawnoff.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sawnoff.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sawnoff.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sawnoff.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sawnoff.reloadTime.upgradedSkill.maxTier;


			fin >> survivalProfiles[i - 1].sawnoff.bulletSpread.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sawnoff.bulletSpread.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sawnoff.bulletSpread.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sawnoff.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sawnoff.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sawnoff.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sawnoff.recoilTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sawnoff.recoilTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sawnoff.recoilTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sawnoff.isBought;
			fin >> survivalProfiles[i - 1].sawnoff.isEquipt;


			//Pump
			fin >> survivalProfiles[i - 1].pumpShotgun.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].pumpShotgun.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].pumpShotgun.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].pumpShotgun.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].pumpShotgun.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].pumpShotgun.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].pumpShotgun.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].pumpShotgun.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].pumpShotgun.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].pumpShotgun.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].pumpShotgun.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].pumpShotgun.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].pumpShotgun.bulletSpread.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].pumpShotgun.bulletSpread.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].pumpShotgun.bulletSpread.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].pumpShotgun.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].pumpShotgun.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].pumpShotgun.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].pumpShotgun.recoilTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].pumpShotgun.recoilTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].pumpShotgun.recoilTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].pumpShotgun.isBought;
			fin >> survivalProfiles[i - 1].pumpShotgun.isEquipt;

			//Auto
			fin >> survivalProfiles[i - 1].autoShotgun.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].autoShotgun.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].autoShotgun.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].autoShotgun.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].autoShotgun.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].autoShotgun.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].autoShotgun.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].autoShotgun.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].autoShotgun.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].autoShotgun.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].autoShotgun.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].autoShotgun.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].autoShotgun.bulletSpread.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].autoShotgun.bulletSpread.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].autoShotgun.bulletSpread.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].autoShotgun.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].autoShotgun.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].autoShotgun.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].autoShotgun.recoilTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].autoShotgun.recoilTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].autoShotgun.recoilTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].autoShotgun.isBought;
			fin >> survivalProfiles[i - 1].autoShotgun.isEquipt;



#pragma endregion

#pragma region Assault Rifles

			//AK-47
			fin >> survivalProfiles[i - 1].ak47.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].ak47.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].ak47.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].ak47.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].ak47.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].ak47.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].ak47.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].ak47.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].ak47.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].ak47.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].ak47.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].ak47.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].ak47.bulletSpread.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].ak47.bulletSpread.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].ak47.bulletSpread.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].ak47.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].ak47.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].ak47.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].ak47.recoilTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].ak47.recoilTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].ak47.recoilTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].ak47.isBought;
			fin >> survivalProfiles[i - 1].ak47.isEquipt;

			//M-16
			fin >> survivalProfiles[i - 1].m16.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].m16.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].m16.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].m16.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].m16.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].m16.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].m16.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].m16.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].m16.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].m16.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].m16.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].m16.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].m16.bulletSpread.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].m16.bulletSpread.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].m16.bulletSpread.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].m16.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].m16.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].m16.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].m16.recoilTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].m16.recoilTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].m16.recoilTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].m16.isBought;
			fin >> survivalProfiles[i - 1].m16.isEquipt;

			//LMG
			fin >> survivalProfiles[i - 1].lmg.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].lmg.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].lmg.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].lmg.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].lmg.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].lmg.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].lmg.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].lmg.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].lmg.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].lmg.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].lmg.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].lmg.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].lmg.bulletSpread.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].lmg.bulletSpread.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].lmg.bulletSpread.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].lmg.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].lmg.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].lmg.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].lmg.recoilTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].lmg.recoilTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].lmg.recoilTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].lmg.isBought;
			fin >> survivalProfiles[i - 1].lmg.isEquipt;

#pragma endregion

#pragma region Heavy Weapons

			//Sniper
			fin >> survivalProfiles[i - 1].sniper.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sniper.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sniper.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sniper.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sniper.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sniper.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sniper.penPower.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sniper.penPower.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sniper.penPower.upgradedSkill.maxTier;


			fin >> survivalProfiles[i - 1].sniper.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sniper.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sniper.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sniper.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sniper.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sniper.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sniper.bulletSpread.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sniper.bulletSpread.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sniper.bulletSpread.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sniper.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sniper.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sniper.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sniper.recoilTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sniper.recoilTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sniper.recoilTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].sniper.isBought;
			fin >> survivalProfiles[i - 1].sniper.isEquipt;

			//Flamethrower

			fin >> survivalProfiles[i - 1].flameThrower.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].flameThrower.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].flameThrower.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].flameThrower.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].flameThrower.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].flameThrower.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].flameThrower.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].flameThrower.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].flameThrower.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].flameThrower.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].flameThrower.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].flameThrower.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].flameThrower.bulletSpread.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].flameThrower.bulletSpread.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].flameThrower.bulletSpread.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].flameThrower.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].flameThrower.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].flameThrower.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].flameThrower.bulletVelocity.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].flameThrower.bulletVelocity.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].flameThrower.bulletVelocity.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].flameThrower.isBought;
			fin >> survivalProfiles[i - 1].flameThrower.isEquipt;

			//Grenade Launcher

			fin >> survivalProfiles[i - 1].nadeLauncher.totalAmmo.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].nadeLauncher.totalAmmo.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].nadeLauncher.totalAmmo.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].nadeLauncher.magSize.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].nadeLauncher.magSize.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].nadeLauncher.magSize.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].nadeLauncher.ammoCap.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].nadeLauncher.ammoCap.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].nadeLauncher.ammoCap.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].nadeLauncher.reloadTime.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].nadeLauncher.reloadTime.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].nadeLauncher.reloadTime.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].nadeLauncher.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].nadeLauncher.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].nadeLauncher.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].nadeLauncher.bulletVelocity.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].nadeLauncher.bulletVelocity.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].nadeLauncher.bulletVelocity.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].nadeLauncher.isBought;
			fin >> survivalProfiles[i - 1].nadeLauncher.isEquipt;

			//Barb Wire
			fin >> survivalProfiles[i - 1].barbWire.maxHealth.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].barbWire.maxHealth.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].barbWire.maxHealth.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].barbWire.damage.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].barbWire.damage.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].barbWire.damage.upgradedSkill.maxTier;

			fin >> survivalProfiles[i - 1].barbWire.isBought;

			for (size_t j = 0; j < 74; j++)
			{

				fin >> survivalProfiles[i - 1].barbWireStates[j];


			}
			//Sandbag

			fin >> survivalProfiles[i - 1].sandBag.maxHealth.upgradedSkill.stat;
			fin >> survivalProfiles[i - 1].sandBag.maxHealth.upgradedSkill.currTier;
			fin >> survivalProfiles[i - 1].sandBag.maxHealth.upgradedSkill.maxTier;


			fin >> survivalProfiles[i - 1].sandBag.isBought;

			for (size_t j = 0; j < 66; j++)
			{

				fin >> survivalProfiles[i - 1].sandBagStates[j];


			}


			fin >> survivalProfiles[i - 1].landMine.isBought;

			for (size_t j = 0; j < 55; j++)
			{

				fin >> survivalProfiles[i - 1].landMineStates[j];


			}

			fin >> survivalProfiles[i - 1].numTurrets;

			fin >> survivalProfiles[i - 1].maxNumTurrets;


			fin >> survivalProfiles[i - 1].wavesComplete;





			//LandMine



#pragma endregion

			fin.close();
		}
	}
}
void				Game::LoadTutorialProfiles(void)
{
	//* If using Wide characters under project settings *//
	HRESULT hr;
	ostringstream stringstream;
	char path[MAX_PATH];
	LPWSTR wszPath = NULL;
	size_t   size;


	// Get the path to the app data folder
	hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, 0, &wszPath);


	// Convert from LPWSTR to char[]
	wcstombs_s(&size, path, MAX_PATH, wszPath, MAX_PATH);


	// Convert char types
	if (hr == S_OK)
		stringstream << path;
	string pathtowrite = stringstream.str();


	// Add the company and game information
	pathtowrite += "\\CTS\\ZombieStrike\\Tutorial\\";


	// Create our directory
	SHCreateDirectoryEx(NULL, pathtowrite.c_str(), 0);


	// Create our save file

	string filePath = pathtowrite;

	filePath += "savefile.save";


	ifstream fin(filePath.c_str());
	if (fin.is_open())
	{
		getline(fin, tutorialProfile.path);

		fin >> tutorialProfile.time.tm_year;

		fin >> tutorialProfile.time.tm_mon;
		fin >> tutorialProfile.time.tm_mday;
		fin >> tutorialProfile.time.tm_hour;
		fin >> tutorialProfile.time.tm_min;
		fin >> tutorialProfile.time.tm_sec;

		fin >> tutorialProfile.health;


#pragma region Pistols

		//pistol
		fin >> tutorialProfile.pistol.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.pistol.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.pistol.magSize.upgradedSkill.maxTier;


		fin >> tutorialProfile.pistol.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.pistol.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.pistol.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.pistol.recoilTime.upgradedSkill.stat;
		fin >> tutorialProfile.pistol.recoilTime.upgradedSkill.currTier;
		fin >> tutorialProfile.pistol.recoilTime.upgradedSkill.maxTier;
		fin >> tutorialProfile.pistol.isEquipt;

		//revolver
		fin >> tutorialProfile.revolver.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.revolver.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.revolver.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.revolver.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.revolver.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.revolver.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.revolver.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.revolver.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.revolver.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.revolver.recoilTime.upgradedSkill.stat;
		fin >> tutorialProfile.revolver.recoilTime.upgradedSkill.currTier;
		fin >> tutorialProfile.revolver.recoilTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.revolver.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.revolver.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.revolver.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.revolver.penPower.upgradedSkill.stat;
		fin >> tutorialProfile.revolver.penPower.upgradedSkill.currTier;
		fin >> tutorialProfile.revolver.penPower.upgradedSkill.maxTier;

		fin >> tutorialProfile.revolver.damage.upgradedSkill.stat;
		fin >> tutorialProfile.revolver.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.revolver.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.revolver.isBought;
		fin >> tutorialProfile.revolver.isEquipt;


#pragma endregion





#pragma region SMGs
		//Mac10
		fin >> tutorialProfile.mac10.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.mac10.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.mac10.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.mac10.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.mac10.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.mac10.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.mac10.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.mac10.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.mac10.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.mac10.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.mac10.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.mac10.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.mac10.bulletSpread.upgradedSkill.stat;
		fin >> tutorialProfile.mac10.bulletSpread.upgradedSkill.currTier;
		fin >> tutorialProfile.mac10.bulletSpread.upgradedSkill.maxTier;

		fin >> tutorialProfile.mac10.damage.upgradedSkill.stat;
		fin >> tutorialProfile.mac10.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.mac10.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.mac10.isBought;
		fin >> tutorialProfile.mac10.isEquipt;

		//Tech9
		fin >> tutorialProfile.tech9.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.tech9.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.tech9.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.tech9.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.tech9.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.tech9.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.tech9.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.tech9.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.tech9.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.tech9.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.tech9.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.tech9.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.tech9.bulletSpread.upgradedSkill.stat;
		fin >> tutorialProfile.tech9.bulletSpread.upgradedSkill.currTier;
		fin >> tutorialProfile.tech9.bulletSpread.upgradedSkill.maxTier;

		fin >> tutorialProfile.tech9.damage.upgradedSkill.stat;
		fin >> tutorialProfile.tech9.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.tech9.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.tech9.isBought;
		fin >> tutorialProfile.tech9.isEquipt;

		//P90
		fin >> tutorialProfile.p90.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.p90.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.p90.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.p90.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.p90.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.p90.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.p90.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.p90.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.p90.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.p90.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.p90.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.p90.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.p90.bulletSpread.upgradedSkill.stat;
		fin >> tutorialProfile.p90.bulletSpread.upgradedSkill.currTier;
		fin >> tutorialProfile.p90.bulletSpread.upgradedSkill.maxTier;

		fin >> tutorialProfile.p90.damage.upgradedSkill.stat;
		fin >> tutorialProfile.p90.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.p90.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.p90.isBought;
		fin >> tutorialProfile.p90.isEquipt;

#pragma endregion

#pragma region Shotguns

		//SawnOff
		fin >> tutorialProfile.sawnoff.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.sawnoff.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.sawnoff.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.sawnoff.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.sawnoff.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.sawnoff.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.sawnoff.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.sawnoff.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.sawnoff.reloadTime.upgradedSkill.maxTier;


		fin >> tutorialProfile.sawnoff.bulletSpread.upgradedSkill.stat;
		fin >> tutorialProfile.sawnoff.bulletSpread.upgradedSkill.currTier;
		fin >> tutorialProfile.sawnoff.bulletSpread.upgradedSkill.maxTier;

		fin >> tutorialProfile.sawnoff.damage.upgradedSkill.stat;
		fin >> tutorialProfile.sawnoff.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.sawnoff.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.sawnoff.recoilTime.upgradedSkill.stat;
		fin >> tutorialProfile.sawnoff.recoilTime.upgradedSkill.currTier;
		fin >> tutorialProfile.sawnoff.recoilTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.sawnoff.isBought;
		fin >> tutorialProfile.sawnoff.isEquipt;


		//Pump
		fin >> tutorialProfile.pumpShotgun.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.pumpShotgun.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.pumpShotgun.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.pumpShotgun.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.pumpShotgun.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.pumpShotgun.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.pumpShotgun.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.pumpShotgun.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.pumpShotgun.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.pumpShotgun.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.pumpShotgun.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.pumpShotgun.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.pumpShotgun.bulletSpread.upgradedSkill.stat;
		fin >> tutorialProfile.pumpShotgun.bulletSpread.upgradedSkill.currTier;
		fin >> tutorialProfile.pumpShotgun.bulletSpread.upgradedSkill.maxTier;

		fin >> tutorialProfile.pumpShotgun.damage.upgradedSkill.stat;
		fin >> tutorialProfile.pumpShotgun.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.pumpShotgun.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.pumpShotgun.recoilTime.upgradedSkill.stat;
		fin >> tutorialProfile.pumpShotgun.recoilTime.upgradedSkill.currTier;
		fin >> tutorialProfile.pumpShotgun.recoilTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.pumpShotgun.isBought;
		fin >> tutorialProfile.pumpShotgun.isEquipt;

		//Auto
		fin >> tutorialProfile.autoShotgun.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.autoShotgun.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.autoShotgun.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.autoShotgun.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.autoShotgun.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.autoShotgun.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.autoShotgun.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.autoShotgun.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.autoShotgun.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.autoShotgun.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.autoShotgun.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.autoShotgun.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.autoShotgun.bulletSpread.upgradedSkill.stat;
		fin >> tutorialProfile.autoShotgun.bulletSpread.upgradedSkill.currTier;
		fin >> tutorialProfile.autoShotgun.bulletSpread.upgradedSkill.maxTier;

		fin >> tutorialProfile.autoShotgun.damage.upgradedSkill.stat;
		fin >> tutorialProfile.autoShotgun.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.autoShotgun.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.autoShotgun.recoilTime.upgradedSkill.stat;
		fin >> tutorialProfile.autoShotgun.recoilTime.upgradedSkill.currTier;
		fin >> tutorialProfile.autoShotgun.recoilTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.autoShotgun.isBought;
		fin >> tutorialProfile.autoShotgun.isEquipt;



#pragma endregion

#pragma region Assault Rifles

		//AK-47
		fin >> tutorialProfile.ak47.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.ak47.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.ak47.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.ak47.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.ak47.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.ak47.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.ak47.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.ak47.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.ak47.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.ak47.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.ak47.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.ak47.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.ak47.bulletSpread.upgradedSkill.stat;
		fin >> tutorialProfile.ak47.bulletSpread.upgradedSkill.currTier;
		fin >> tutorialProfile.ak47.bulletSpread.upgradedSkill.maxTier;

		fin >> tutorialProfile.ak47.damage.upgradedSkill.stat;
		fin >> tutorialProfile.ak47.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.ak47.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.ak47.recoilTime.upgradedSkill.stat;
		fin >> tutorialProfile.ak47.recoilTime.upgradedSkill.currTier;
		fin >> tutorialProfile.ak47.recoilTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.ak47.isBought;
		fin >> tutorialProfile.ak47.isEquipt;

		//M-16
		fin >> tutorialProfile.m16.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.m16.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.m16.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.m16.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.m16.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.m16.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.m16.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.m16.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.m16.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.m16.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.m16.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.m16.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.m16.bulletSpread.upgradedSkill.stat;
		fin >> tutorialProfile.m16.bulletSpread.upgradedSkill.currTier;
		fin >> tutorialProfile.m16.bulletSpread.upgradedSkill.maxTier;

		fin >> tutorialProfile.m16.damage.upgradedSkill.stat;
		fin >> tutorialProfile.m16.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.m16.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.m16.recoilTime.upgradedSkill.stat;
		fin >> tutorialProfile.m16.recoilTime.upgradedSkill.currTier;
		fin >> tutorialProfile.m16.recoilTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.m16.isBought;
		fin >> tutorialProfile.m16.isEquipt;

		//LMG
		fin >> tutorialProfile.lmg.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.lmg.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.lmg.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.lmg.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.lmg.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.lmg.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.lmg.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.lmg.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.lmg.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.lmg.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.lmg.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.lmg.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.lmg.bulletSpread.upgradedSkill.stat;
		fin >> tutorialProfile.lmg.bulletSpread.upgradedSkill.currTier;
		fin >> tutorialProfile.lmg.bulletSpread.upgradedSkill.maxTier;

		fin >> tutorialProfile.lmg.damage.upgradedSkill.stat;
		fin >> tutorialProfile.lmg.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.lmg.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.lmg.recoilTime.upgradedSkill.stat;
		fin >> tutorialProfile.lmg.recoilTime.upgradedSkill.currTier;
		fin >> tutorialProfile.lmg.recoilTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.lmg.isBought;
		fin >> tutorialProfile.lmg.isEquipt;

#pragma endregion

#pragma region Heavy Weapons

		//Sniper
		fin >> tutorialProfile.sniper.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.sniper.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.sniper.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.sniper.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.sniper.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.sniper.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.sniper.penPower.upgradedSkill.stat;
		fin >> tutorialProfile.sniper.penPower.upgradedSkill.currTier;
		fin >> tutorialProfile.sniper.penPower.upgradedSkill.maxTier;


		fin >> tutorialProfile.sniper.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.sniper.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.sniper.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.sniper.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.sniper.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.sniper.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.sniper.bulletSpread.upgradedSkill.stat;
		fin >> tutorialProfile.sniper.bulletSpread.upgradedSkill.currTier;
		fin >> tutorialProfile.sniper.bulletSpread.upgradedSkill.maxTier;

		fin >> tutorialProfile.sniper.damage.upgradedSkill.stat;
		fin >> tutorialProfile.sniper.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.sniper.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.sniper.recoilTime.upgradedSkill.stat;
		fin >> tutorialProfile.sniper.recoilTime.upgradedSkill.currTier;
		fin >> tutorialProfile.sniper.recoilTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.sniper.isBought;
		fin >> tutorialProfile.sniper.isEquipt;

		//Flamethrower

		fin >> tutorialProfile.flameThrower.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.flameThrower.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.flameThrower.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.flameThrower.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.flameThrower.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.flameThrower.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.flameThrower.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.flameThrower.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.flameThrower.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.flameThrower.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.flameThrower.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.flameThrower.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.flameThrower.bulletSpread.upgradedSkill.stat;
		fin >> tutorialProfile.flameThrower.bulletSpread.upgradedSkill.currTier;
		fin >> tutorialProfile.flameThrower.bulletSpread.upgradedSkill.maxTier;

		fin >> tutorialProfile.flameThrower.damage.upgradedSkill.stat;
		fin >> tutorialProfile.flameThrower.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.flameThrower.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.flameThrower.bulletVelocity.upgradedSkill.stat;
		fin >> tutorialProfile.flameThrower.bulletVelocity.upgradedSkill.currTier;
		fin >> tutorialProfile.flameThrower.bulletVelocity.upgradedSkill.maxTier;

		fin >> tutorialProfile.flameThrower.isBought;
		fin >> tutorialProfile.flameThrower.isEquipt;

		//Grenade Launcher

		fin >> tutorialProfile.nadeLauncher.totalAmmo.upgradedSkill.stat;
		fin >> tutorialProfile.nadeLauncher.totalAmmo.upgradedSkill.currTier;
		fin >> tutorialProfile.nadeLauncher.totalAmmo.upgradedSkill.maxTier;

		fin >> tutorialProfile.nadeLauncher.magSize.upgradedSkill.stat;
		fin >> tutorialProfile.nadeLauncher.magSize.upgradedSkill.currTier;
		fin >> tutorialProfile.nadeLauncher.magSize.upgradedSkill.maxTier;

		fin >> tutorialProfile.nadeLauncher.ammoCap.upgradedSkill.stat;
		fin >> tutorialProfile.nadeLauncher.ammoCap.upgradedSkill.currTier;
		fin >> tutorialProfile.nadeLauncher.ammoCap.upgradedSkill.maxTier;

		fin >> tutorialProfile.nadeLauncher.reloadTime.upgradedSkill.stat;
		fin >> tutorialProfile.nadeLauncher.reloadTime.upgradedSkill.currTier;
		fin >> tutorialProfile.nadeLauncher.reloadTime.upgradedSkill.maxTier;

		fin >> tutorialProfile.nadeLauncher.damage.upgradedSkill.stat;
		fin >> tutorialProfile.nadeLauncher.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.nadeLauncher.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.nadeLauncher.bulletVelocity.upgradedSkill.stat;
		fin >> tutorialProfile.nadeLauncher.bulletVelocity.upgradedSkill.currTier;
		fin >> tutorialProfile.nadeLauncher.bulletVelocity.upgradedSkill.maxTier;

		fin >> tutorialProfile.nadeLauncher.isBought;
		fin >> tutorialProfile.nadeLauncher.isEquipt;

		//Barb Wire
		fin >> tutorialProfile.barbWire.maxHealth.upgradedSkill.stat;
		fin >> tutorialProfile.barbWire.maxHealth.upgradedSkill.currTier;
		fin >> tutorialProfile.barbWire.maxHealth.upgradedSkill.maxTier;

		fin >> tutorialProfile.barbWire.damage.upgradedSkill.stat;
		fin >> tutorialProfile.barbWire.damage.upgradedSkill.currTier;
		fin >> tutorialProfile.barbWire.damage.upgradedSkill.maxTier;

		fin >> tutorialProfile.barbWire.isBought;

		for (size_t j = 0; j < 28; j++)
		{

			fin >> tutorialProfile.barbWireStates[j];


		}
		//Sandbag

		fin >> tutorialProfile.sandBag.maxHealth.upgradedSkill.stat;
		fin >> tutorialProfile.sandBag.maxHealth.upgradedSkill.currTier;
		fin >> tutorialProfile.sandBag.maxHealth.upgradedSkill.maxTier;


		fin >> tutorialProfile.sandBag.isBought;

		for (size_t j = 0; j < 38; j++)
		{

			fin >> tutorialProfile.sandBagStates[j];


		}


		fin >> tutorialProfile.landMine.isBought;

		for (size_t j = 0; j < 28; j++)
		{

			fin >> tutorialProfile.landMineStates[j];


		}

		fin >> tutorialProfile.numTurrets;

		fin >> tutorialProfile.maxNumTurrets;


		fin >> tutorialProfile.wavesComplete;





		//LandMine
	}
}

/**************************************************************/
// CreateProfiles
void Game::CreateStoryProfiles()
{

	//* If using Wide characters under project settings *//
	HRESULT hr;
	ostringstream stringstream;
	char path[MAX_PATH];
	LPWSTR wszPath = NULL;
	size_t   size;

	time_t tempTime;
	time(&tempTime);

	tm localTime;
	localtime_s(&localTime, &tempTime);




	// Get the path to the app data folder
	hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, 0, &wszPath);


	// Convert from LPWSTR to char[]
	wcstombs_s(&size, path, MAX_PATH, wszPath, MAX_PATH);


	// Convert char types
	if (hr == S_OK)
		stringstream << path;
	string pathtowrite = stringstream.str();


	// Add the company and game information
	pathtowrite += "\\CTS\\ZombieStrike\\Story\\";


	// Create our directory
	if (SHCreateDirectoryEx(NULL, pathtowrite.c_str(), 0) == ERROR_SUCCESS)
	{
		// Create our save file
		for (unsigned int i = 1; i < 4; i++)
		{
			string filePath = pathtowrite;

			filePath += "savefile.save";
			filePath += std::to_string(i);



			fstream fout(filePath.c_str(), std::ios_base::out);
			if (fout.is_open())
			{
				WeaponManager::GetInstance()->GetWeapons();
				fout << filePath << '\n';

				fout << (localTime.tm_year + 1900) << '\n';
				fout << (localTime.tm_mon + 1) << '\n';
				fout << localTime.tm_mday << '\n';
				fout << localTime.tm_hour << '\n';
				fout << localTime.tm_min << '\n';
				fout << localTime.tm_sec << '\n';

				//health
				fout << 100  << '\n';


#pragma region Pistols

				//pistol stats
				fout << 10 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .33 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';

				//revolver
				fout << 25 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 25 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 50 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

#pragma endregion

#pragma region SMGs
				//Mac10
				fout << 60 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 20 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 60 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 20 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//Tech9
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 30 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 35 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//p90
				fout << 150 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 50 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 150 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 35 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';


#pragma endregion

#pragma region Shotguns
				//sawn off
				fout << 16 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 16 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 20 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 35 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//pump
				fout << 24 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 6 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 24 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 4 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 10 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 25 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//auto shotty
				fout << 30 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 10 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 30 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 15 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 25 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';


			


#pragma endregion


#pragma region Assault Rifles
				//ak47
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 30 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 7 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 40 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .33 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//m16
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 30 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 25 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n'; 
				fout << 0 << '\n';

				//LMG
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 100 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 6 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 75 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .33 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';


#pragma endregion


#pragma region Heavy Weapons
				//sniper
				fout << 15 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 15 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n'; 
				//flamethrower
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 100 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 4 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 10 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 20 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 300 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//grenade launcher
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 4 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 300 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';



				//barbedwire
				fout << 100 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';

				fout << 10 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';

				fout << 0 << '\n';

				for (size_t i = 0; i < 74; i++)
				{
					fout << 0 << '\n';
				}

				//sandbags
				fout << 250 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';

				fout << 1 << '\n';

				for (size_t i = 0; i < 66; i++)
				{
					fout << 1 << '\n';
				}

				//landmines
				fout << 0 << '\n';

				for (size_t i = 0; i < 55; i++)
				{
					fout << 0 << '\n';
				}


				//turrets
				//numturrets
				fout << 0 << '\n';
				//max num turrets
				fout << 3 << '\n';

				//num waves
				fout << 0;

#pragma endregion

				fout.close();
			}
		}
	}
}
void Game::CreateSurvivalProfiles()
{
	//* If using Wide characters under project settings *//
	HRESULT hr;
	ostringstream stringstream;
	char path[MAX_PATH];
	LPWSTR wszPath = NULL;
	size_t   size;

	time_t tempTime;
	time(&tempTime);

	tm localTime;
	localtime_s(&localTime, &tempTime);


	// Get the path to the app data folder
	hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, 0, &wszPath);


	// Convert from LPWSTR to char[]
	wcstombs_s(&size, path, MAX_PATH, wszPath, MAX_PATH);


	// Convert char types
	if (hr == S_OK)
		stringstream << path;
	string pathtowrite = stringstream.str();


	// Add the company and game information
	pathtowrite += "\\CTS\\ZombieStrike\\Survival\\";


	// Create our directory
	if (SHCreateDirectoryEx(NULL, pathtowrite.c_str(), 0) == ERROR_SUCCESS)
	{
		// Create our save file
		for (unsigned int i = 1; i < 4; i++)
		{
			string filePath = pathtowrite;

			filePath += "savefile.save";
			filePath += std::to_string(i);



			fstream fout(filePath.c_str(), std::ios_base::out);
			if (fout.is_open())
			{
				
				fout << filePath << '\n';

				fout << (localTime.tm_year + 1900) << '\n';
				fout << (localTime.tm_mon + 1) << '\n';
				fout << localTime.tm_mday << '\n';
				fout << localTime.tm_hour << '\n';
				fout << localTime.tm_min << '\n';
				fout << localTime.tm_sec << '\n';

				fout << 100 << '\n';


#pragma region Pistols

				//pistol stats
				fout << 10 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .33 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';

				//revolver
				fout << 25 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 25 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 50 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

#pragma endregion

#pragma region SMGs
				//Mac10
				fout << 60 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 20 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 60 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 20 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//Tech9
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 30 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 35 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//p90
				fout << 150 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 50 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 150 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 35 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';


#pragma endregion

#pragma region Shotguns
				//sawn off
				fout << 16 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 16 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 20 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 35 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//pump
				fout << 24 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 6 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 24 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 4 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 10 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 25 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//auto shotty
				fout << 30 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 10 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 30 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 15 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 25 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';





#pragma endregion


#pragma region Assault Rifles
				//ak47
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 30 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 7 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 40 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .33 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//m16
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 30 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 90 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 25 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//LMG
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 100 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 6 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 75 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << .33 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';


#pragma endregion


#pragma region Heavy Weapons
				//sniper
				fout << 15 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 15 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 2 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';
				//flamethrower
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 100 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 4 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 10 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 20 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 300 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';

				//grenade launcher
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 1 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 5 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 4 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 200 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 300 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';
				fout << 0 << '\n';
				fout << 0 << '\n';



				//barbedwire
				fout << 100 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';

				fout << 10 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';

				fout << 0 << '\n';

				for (size_t i = 0; i < 74; i++)
				{
					fout << 0 << '\n';
				}

				//sandbags
				fout << 250 << '\n';
				fout << 1 << '\n';
				fout << 3 << '\n';

				fout << 1 << '\n';

				for (size_t i = 0; i < 66; i++)
				{
					fout << 1 << '\n';
				}

				//landmines
				fout << 0 << '\n';

				for (size_t i = 0; i < 55; i++)
				{
					fout << 0 << '\n';
				}


				//turrets
				//numturrets
				fout << 0 << '\n';
				//max num turrets
				fout << 3 << '\n';

				//num waves
				fout << 0;
			}
		}
	}
}

void Game::OverWriteProfile(GamerProfile& profile)
{
	time_t tempTime;
	time(&tempTime);

	tm localTime;
	localtime_s(&localTime, &tempTime);

	string filePath = profile.path;

	fstream fout(filePath.c_str(), std::ios_base::out);
	if (fout.is_open())
	{
		
		fout << filePath << '\n';


		fout << (localTime.tm_year + 1900) << '\n';
		fout << (localTime.tm_mon + 1) << '\n';
		fout << localTime.tm_mday << '\n';
		fout << localTime.tm_hour << '\n';
		fout << localTime.tm_min << '\n';
		fout << localTime.tm_sec << '\n';

		fout << 100 << '\n';

#pragma region Pistols

		//pistol stats
		fout << 10 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 2 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .33 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';

		//revolver
		fout << 25 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 25 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 50 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

#pragma endregion

#pragma region SMGs
		//Mac10
		fout << 60 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 20 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 60 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 4 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 20 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//Tech9
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 30 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 35 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//p90
		fout << 150 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 50 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 150 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 35 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';


#pragma endregion

#pragma region Shotguns
		//sawn off
		fout << 16 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 16 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 2 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 20 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 35 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//pump
		fout << 24 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 6 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 24 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 4 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 10 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 25 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//auto shotty
		fout << 30 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 10 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 30 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 15 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 25 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';





#pragma endregion


#pragma region Assault Rifles
		//ak47
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 30 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 7 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 40 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .33 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//m16
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 30 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 25 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .2 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//LMG
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 100 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 6 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 75 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .33 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';


#pragma endregion


#pragma region Heavy Weapons
		//sniper
		fout << 15 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 2 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 15 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 2 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';
		//flamethrower
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 100 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 4 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 10 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 20 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 300 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//grenade launcher
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 4 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 300 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';


		//barbedwire
		fout << 100 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';

		fout << 10 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';

		fout << 0 << '\n';

		for (size_t i = 0; i < 74; i++)
		{
			fout << 0 << '\n';
		}

		//sandbags
		fout << 250 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';

		fout << 1 << '\n';

		for (size_t i = 0; i < 66; i++)
		{
			fout << 1 << '\n';
		}

		//landmines
		fout << 0 << '\n';

		for (size_t i = 0; i < 55; i++)
		{
			fout << 0 << '\n';
		}


		//turrets
		//numturrets
		fout << 0 << '\n';
		//max num turrets
		fout << 3 << '\n';

		//num waves
		fout << 0;

		fout.close();
	}
}

void Game::CreateTutorialProfile(void)
{
//* If using Wide characters under project settings *//
HRESULT hr;
ostringstream stringstream;
char path[MAX_PATH];
LPWSTR wszPath = NULL;
size_t   size;

time_t tempTime;
time(&tempTime);

tm localTime;
localtime_s(&localTime, &tempTime);

// Get the path to the app data folder
hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, 0, &wszPath);


// Convert from LPWSTR to char[]
wcstombs_s(&size, path, MAX_PATH, wszPath, MAX_PATH);


// Convert char types
if (hr == S_OK)
stringstream << path;
string pathtowrite = stringstream.str();


// Add the company and game information
pathtowrite += "\\CTS\\ZombieStrike\\Tutorial\\";


// Create our directory
SHCreateDirectoryEx(NULL, pathtowrite.c_str(), 0);


// Create our save file
	string filePath = pathtowrite;

	filePath += "savefile.save";
	//filePath += std::to_string(i);

	ofstream fout(filePath.c_str());
	if (fout.is_open())
	{

		fout << filePath << '\n';


		fout << (localTime.tm_year + 1900) << '\n';
		fout << (localTime.tm_mon + 1) << '\n';
		fout << localTime.tm_mday << '\n';
		fout << localTime.tm_hour << '\n';
		fout << localTime.tm_min << '\n';
		fout << localTime.tm_sec << '\n';

		fout << 100 << '\n';

#pragma region Pistols

		//pistol stats
		fout << 10 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 2 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .33 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';

		//revolver
		fout << 25 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 25 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 50 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

#pragma endregion

#pragma region SMGs
		//Mac10
		fout << 60 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 20 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 60 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 4 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 20 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//Tech9
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 30 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 35 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//p90
		fout << 150 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 50 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 150 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 35 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';


#pragma endregion

#pragma region Shotguns
		//sawn off
		fout << 16 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 16 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 2 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 20 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 35 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//pump
		fout << 24 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 6 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 24 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 4 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 10 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 25 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//auto shotty
		fout << 30 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 10 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 30 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 15 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 25 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';





#pragma endregion


#pragma region Assault Rifles
		//ak47
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 30 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 7 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 40 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .33 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//m16
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 30 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 90 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 25 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .2 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//LMG
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 100 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 6 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 75 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << .33 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';


#pragma endregion


#pragma region Heavy Weapons
		//sniper
		fout << 15 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 2 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 15 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 2 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';
		//flamethrower
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 100 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 4 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 10 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 20 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 300 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';

		//grenade launcher
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 1 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 5 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 4 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 200 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 300 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';
		fout << 0 << '\n';
		fout << 0 << '\n';


		//barbedwire
		fout << 100 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';

		fout << 10 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';

		fout << 0 << '\n';

		for (size_t i = 0; i < 28; i++)
		{
			fout << 0 << '\n';
		}

		//sandbags
		fout << 250 << '\n';
		fout << 1 << '\n';
		fout << 3 << '\n';

		fout << 1 << '\n';

		for (size_t i = 0; i < 28; i++)
		{
			fout << 1 << '\n';
		}

		//landmines
		fout << 0 << '\n';

		for (size_t i = 0; i < 28; i++)
		{
			fout << 0 << '\n';
		}


		//turrets
		//numturrets
		fout << 0 << '\n';
		//max num turrets
		fout << 3 << '\n';

		//num waves
		fout << 0;

#pragma endregion

		fout.close();
	}
}