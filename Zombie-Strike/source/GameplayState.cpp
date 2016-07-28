#include "GameplayState.h"

#include "Game.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "WinGameState.h"
#include "LoseGameState.h"
#include "ShopState.h"

#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"
#include "../SGD Wrappers/SGD_EventManager.h"
#include "../SGD Wrappers/SGD_Event.h"

#include "../SGD Wrappers/SGD_Event.h"
#include "../SGD Wrappers/SGD_MessageManager.h"
#include "../SGD Wrappers/SGD_Message.h"
#include "MessageID.h"
#include "DestroyObjectMessage.h"
#include "CreatePistolBullet.h"
#include "CreateShotgunBullet.h"
#include "CreateARifleBullet.h"
#include "CreateSniperBullet.h"
#include "CreateFlameBullet.h"
#include "CreateGrenadeBullet.h"
#include "CreatePukeBullet.h"
#include "CreateTurretBullet.h"
#include "Spawner.h"
#include "SpawnManager.h"

#include "WeaponManager.h"
#include "CreateZombieMessage.h"
#include "CreateFastZombieMsg.h"
#include "CreateFatZombieMsg.h"
#include "CreateExplodingZombieMsg.h"
#include "CreateTankZombieMsg.h"
#include "CreateTurretMessage.h"
#include "CreateBloodMsg.h"
#include "BitmapFont.h"

#include "EntityManager.h"
#include "BaseObject.h"
#include "MovingObject.h"
#include "Player.h"
#include "Zombie.h"
#include "FastZombie.h"
#include "FatZombie.h"
#include "ExplodingZombie.h"
#include "TankZombie.h"

#include "Turret.h"
#include "Bullet.h"
#include "PickUp.h"
#include "Weapon.h"
#include "BloodSplatter.h"

#include "BehaviorManager.h"
#include "AnimationManager.h"
#include "Animation.h"
#include "Frame.h"
#include "MapManager.h"
#include "HTPGameState.h"

#include <Windows.h>
#include <cstdlib>
#include <cassert>
#define WIN32_LEAN_AND_MEAN

/**************************************************************/
// GetInstance
//	- allocate static global instance
//	- return THE instance
/*static*/ GameplayState* GameplayState::GetInstance( void )
{
	static GameplayState s_Instance;	// stored in global memory once
	return &s_Instance;
}

/**************************************************************/
// Enter
//	- reset game
//	- load resources
//	- set up entities
/*virtual*/ void GameplayState::Enter( void )
{

	SpawnManager::GetInstance()->ShutDown();
	HTPGameState::GetInstance()->SetChoiceScreen(true);

	// Set background color
	SGD::GraphicsManager::GetInstance()->SetClearColor( {0, 0, 0} );	// black

	// Initialize the Event & Message Managers
	SGD::EventManager::GetInstance()->Initialize();
	SGD::MessageManager::GetInstance()->Initialize( &MessageProc );

	// Allocate the Entity Manager
	m_pEntities = new EntityManager;


	// Initializ the Behavior Manager
	BehaviorManager::GetInstance()->Initialize();


	/**************************/
	// Load the assets
	/**************************/
	SGD::GraphicsManager*	pGraphics			= SGD::GraphicsManager::GetInstance();
	SGD::AudioManager*		pAudio				= SGD::AudioManager::GetInstance();
	SGD::InputManager*		pInput				= SGD::InputManager::GetInstance();
	//AnimationManager*		pAnimationManager	= AnimationManager::GetInstance();

	



	if (m_bStoryMode == true)
	{
		Game::GetInstance()->LoadStoryProfiles();
		MapManager::GetInstance()->LoadLevel(Game::GetInstance()->GetStoryProfile(), m_pEntities);
		SpawnManager::GetInstance()->LoadFromFile("resource/config/levels/waves.txt");
		SpawnManager::GetInstance()->SetCurrWave(Game::GetInstance()->GetStoryProfile().wavesComplete);
	}
	else
	{
		Game::GetInstance()->LoadSurvivalProfiles();
		MapManager::GetInstance()->LoadLevel(Game::GetInstance()->GetSurvivalProfile(), m_pEntities);
		SpawnManager::GetInstance()->LoadFromFile("resource/config/levels/waves2.txt");
		SpawnManager::GetInstance()->SetCurrWave(Game::GetInstance()->GetSurvivalProfile().wavesComplete);
	}


	
	


	// Music
	//storyMusic		= pAudio->LoadAudio("resource/audio/AmbienceDrama.xwm");
	survivalMusic	= pAudio->LoadAudio("resource/audio/AmbienceDungeon.xwm");
	//m_bStoryMode == true ? pAudio->PlayAudio(storyMusic, true) : pAudio->PlayAudio(survivalMusic, true);
	pAudio->PlayAudio(m_bStoryMode == true ? Game::GetInstance()->storyMusic : survivalMusic, true);


	// SFX
	//playerDeath			= pAudio->LoadAudio("resource/audio/player_death1.wav");
	//playerHurt1			= pAudio->LoadAudio("resource/audio/player_grunt1.wav");
	//playerHurt2			= pAudio->LoadAudio("resource/audio/player_grunt2.wav");
	//playerHurt3			= pAudio->LoadAudio("resource/audio/player_grunt3.wav");
	//cannot_use_skill	= pAudio->LoadAudio("resource/audio/cannotUseAbility7.wav");
	//footstep			= pAudio->LoadAudio("resource/audio/FootstepsWood.wav");
	//m_hWpnSwitch		= Game::GetInstance()->m_hWpnSwitch;
	

	//m_hHudWpn =				Game::GetInstance()
	//turretfire			= pAudio->LoadAudio("resource/audio/TurretFire.wav");

	//zombie_pain			= pAudio->LoadAudio("resource/audio/zombie_howl.wav");
	//bullet_hit_zombie	= pAudio->LoadAudio("resource/audio/bullet_hit_zombie.wav");
	//bullet_hit_house	= pAudio->LoadAudio("resource/audio/bullet_hit_house.wav");
	//out_of_ammo			= pAudio->LoadAudio("resource/audio/out_of_ammo.wav");
	//reload_begin		= pAudio->LoadAudio("resource/audio/reload_begin.wav");
	//reload_finish		= pAudio->LoadAudio("resource/audio/reload_finish.wav");
	//explosion			= pAudio->LoadAudio("resource/audio/Splode2.wav");
	//vomit_hit_player	= pAudio->LoadAudio("resource/audio/splat.wav");

	//pistol_fire			= pAudio->LoadAudio("resource/audio/pistol_fire.wav");
	//shotgun_fire		= pAudio->LoadAudio("resource/audio/shotgun_fire.wav");
	//rifle_fire			= pAudio->LoadAudio("resource/audio/rifle_fire.wav");
	//sniper_fire			= pAudio->LoadAudio("resource/audio/sniper_fire.wav");
	//flamethrower_fire	= pAudio->LoadAudio("resource/audio/fire_ignite_1.wav");
	//smg_fire			= pAudio->LoadAudio("resource/audio/smg_fire_1.wav");
	//rpg_fire			= pAudio->LoadAudio("resource/audio/RocketLauncher.wav");
	//vomit_fire			= pAudio->LoadAudio("resource/audio/vomit.wav");


	//m_hMain = &MainMenuState::GetInstance()->m_hMainTheme;
	//m_hSurvive = &MainMenuState::GetInstance()->m_hSurvivalTheme;

	// Setup the camera
	camera.SetSize({ Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() });

	// Create the main entities
	m_pPlayer = CreatePlayer();
	m_pEntities->AddEntity(m_pPlayer, EntityBucket::BUCKET_PLAYER);

	MovingObject * pPlayer = dynamic_cast<MovingObject*>(m_pPlayer);
	
	
	WeaponManager::GetInstance()->Initialize(*pPlayer);

	UpdateWeaponManager();

	//pPlayer->Release();
	//pPlayer = nullptr;

	
	m_tNextWave.AddTime(3);
	m_tStartWave.AddTime(3);
	m_tCompleteWave.AddTime(3);
}


/**************************************************************/
// Exit
//	- deallocate entities
//	- unload resources
/*virtual*/ void GameplayState::Exit( void )
{
	SGD::Event gameOverMsg = { "GAME_OVER", nullptr, this };
	gameOverMsg.SendEventNow();


	/**************************/
	// Unload the assets
	/**************************/
	SGD::GraphicsManager*	pGraphics	= SGD::GraphicsManager::GetInstance();
	SGD::AudioManager*		pAudio		= SGD::AudioManager::GetInstance();
	SGD::InputManager*		pInput		= SGD::InputManager::GetInstance();
	
	pGraphics->UnloadTexture(MapManager::GetInstance()->GetMapTexture());
	//pGraphics->UnloadTexture(Game::GetInstance()->m_hReticleImage);

	if (pAudio->IsAudioPlaying(Game::GetInstance()->storyMusic) == true)
		pAudio->StopAudio(Game::GetInstance()->storyMusic);
	if (pAudio->IsAudioPlaying(survivalMusic) == true)
		pAudio->StopAudio(survivalMusic);

	pAudio->UnloadAudio(survivalMusic);
	
	

	//pAudio->UnloadAudio(*m_hMain);
	//pAudio->UnloadAudio(*m_hSurvive);

	camera.SetTarget(nullptr);




	// Terminate the Behavior Manager
	BehaviorManager::GetInstance()->Terminate();
	
	WeaponManager::GetInstance()->Exit();
	
	// Deallocate the Entity Manager
	m_pEntities->RemoveAll();
	delete m_pEntities;
	m_pEntities = nullptr;

	if (m_pPlayer != nullptr)
		m_pPlayer->Release();

	m_pPlayer = nullptr;


	// Shutdown & release the Map & Animation Managers
	MapManager::GetInstance()->UnloadLevel();
	//AnimationManager::GetInstance()->Shutdown();
	SpawnManager::GetInstance()->ShutDown();

	

	// Terminate & deallocate the SGD wrappers

	SGD::EventManager::GetInstance()->Terminate();
	SGD::EventManager::DeleteInstance();
	SGD::MessageManager::GetInstance()->Terminate();
	SGD::MessageManager::DeleteInstance();
}


/**************************************************************/
// Input
//	- handle user input
/*virtual*/ bool GameplayState::Input( void )
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();


	/**********************************************************/
	// Press Escape to enter Pause menu
	/**********************************************************/
	if (pInput->IsKeyPressed(SGD::Key::Escape) == true || pInput->IsButtonPressed(0, 9) == true)
	{
		SGD::Event msg("PAUSE");
		msg.SendEventNow();
		Game::GetInstance()->AddState(PauseState::GetInstance());
	}


	/**********************************************************/
	// 'Alt + Tab' -> Pause Menu
	/**********************************************************/
	//if (pInput->IsKeyDown(SGD::Key::Alt) == true && pInput->IsKeyPressed(SGD::Key::Tab) == true)
	//{
	//	SGD::Event msg("PAUSE");
	//	msg.SendEventNow();
	//	Game::GetInstance()->AddState(PauseState::GetInstance());
	//}




	//WeaponManager::GetInstance()->Input();

	/**********************************************************/
	// Player Died!
	/**********************************************************/
	int numframes = AnimationManager::GetInstance()->GetAnimation("playerDeath")->GetFrames().size();
	numframes--;

	if (m_pPlayer->GetAnimation() == "playerDeath" && m_pPlayer->GetAnimationStamp().m_nCurrFrame == numframes)
	{
		SGD::Event msg("PAUSE");
		msg.SendEventNow();
		Game::GetInstance()->AddState(LoseGameState::GetInstance());


		if (pAudio->IsAudioPlaying(Game::GetInstance()->storyMusic) == true)
			pAudio->StopAudio(Game::GetInstance()->storyMusic);
		if (pAudio->IsAudioPlaying(survivalMusic) == true)
			pAudio->StopAudio(survivalMusic);
	}
	
	




	return true;	// keep playing
}


/**************************************************************/
// Update
//	- update game entities
/*virtual*/ void GameplayState::Update( float dt )
{
	WeaponManager::GetInstance()->Update(dt);
	SpawnManager * eSpawner = SpawnManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	Player* player = dynamic_cast<Player*>(m_pPlayer);


	if (player->isLevelCompleted() == false)
	{
		// Update the entities
		eSpawner->Update(dt);
		m_pEntities->UpdateAll(dt);


		// Check collisions
		m_pEntities->CheckCollisions(BUCKET_PLAYER, BUCKET_ENEMIES);
		m_pEntities->CheckCollisions(BUCKET_PLAYER, BUCKET_COLLIDABLE);
		m_pEntities->CheckCollisions(BUCKET_PLAYER, BUCKET_PUKE);
		m_pEntities->CheckCollisions(BUCKET_PLAYER, BUCKET_ENVIRO);

		m_pEntities->CheckCollisions(BUCKET_ENEMIES, BUCKET_ENVIRO);
		m_pEntities->CheckCollisions(BUCKET_ENEMIES, BUCKET_ENEMIES);

		m_pEntities->CheckCollisions(BUCKET_ENEMIES, BUCKET_BULLETS);
		m_pEntities->CheckCollisions(BUCKET_PICKUPS, BUCKET_BULLETS);	// house + bullets
		m_pEntities->CheckCollisions(BUCKET_PICKUPS, BUCKET_ENEMIES);	// house + zombies
		m_pEntities->CheckCollisions(BUCKET_PICKUPS, BUCKET_PLAYER);	// house + player


		// Center camera on the player
		SGD::Point playerpos = m_pPlayer->GetPosition();
		playerpos.x -= Game::GetInstance()->GetScreenWidth() * 0.50f;
		playerpos.y -= Game::GetInstance()->GetScreenHeight() * 0.50f;
		camera.SetPostion(playerpos);

		
		// Process the events & messages
		SGD::EventManager::GetInstance()->Update();
		SGD::MessageManager::GetInstance()->Update();
		MapManager::GetInstance()->Update(dt); 
		
		if (m_tStartWave.Update(dt))
		{
			SpawnManager::GetInstance()->Activate();
		}

		// Update the Map Manager
	//	MapManager::GetInstance()->Update(dt);

	}

	else
	{
		Game::GetInstance()->RemoveState();
		Game::GetInstance()->AddState(GameplayState::GetInstance());
	}


	if (SpawnManager::GetInstance()->GetEnemiesKilled() == SpawnManager::GetInstance()->GetNumWaveEnemies())
	{
		SpawnManager::GetInstance()->Deactivate();

		
		if (SpawnManager::GetInstance()->GetCurrWave() == SpawnManager::GetInstance()->GetNumWaves() - 1)
		{
			// start timer to go to WinState
			if (SpawnManager::GetInstance()->GetGameWon() == false)
				m_tToWinState.AddTime(5.0F);

			// WinState sequence start
			SpawnManager::GetInstance()->SetGameWon(true);

			
			// go to WinState
			if (m_tToWinState.Update(dt) == true)
			{
				if (pAudio->IsAudioPlaying(Game::GetInstance()->storyMusic) == true)
					pAudio->StopAudio(Game::GetInstance()->storyMusic);
				if (pAudio->IsAudioPlaying(survivalMusic) == true)
					pAudio->StopAudio(survivalMusic);

				Game::GetInstance()->AddState(WinGameState::GetInstance());
				return;
			}
		}
		else
		{
			if (m_tNextWave.Update(dt))
			{
				if (m_bStoryMode == true)
					Game::GetInstance()->GetStoryProfile().wavesComplete++;

				else
					Game::GetInstance()->GetSurvivalProfile().wavesComplete++;

				m_bShopState = true;

				m_tNextWave.AddTime(3);

				m_tStartWave.AddTime(3);

				SGD::Event msg("PAUSE");
				msg.SendEventNow();



				//Calls the shopstate//
				Game::GetInstance()->AddState(ShopState::GetInstance());
				player->SetPosition({ m_szWorldSize.width * .6f, m_szWorldSize.height * .6f });




				SGD::Event housemsg("REPAIR_HOUSE");
				housemsg.SendEventNow();

			}
		}

	
	}

	
	//ShopState::GetInstance()->Update(dt);
	

}


/**************************************************************/
// Render
//	- render the game entities
/*virtual*/ void GameplayState::Render( void )
{
	Player* player = dynamic_cast<Player*>(m_pPlayer);

	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	const BitmapFont * pFont = Game::GetInstance()->GetFont();

	SGD::Point textPos({ Game::GetInstance()->GetScreenWidth() / 2, Game::GetInstance()->GetScreenHeight() / 2 });

	// Draw background
	MapManager::GetInstance()->Render();

	// Render the entities
	m_pEntities->RenderAll();

	// Draw status bars
	float top	= 450;
	float left	= 435;

	float tops	= 475;
	float lefts	= 435;

	WeaponManager::GetInstance()->Render();

	if (m_tStartWave.GetTime() > 0.0f && m_bShopState == false && SpawnManager::GetInstance()->GetGameWon() == false)
	{
		stringstream nWave;
		nWave << "Wave " << SpawnManager::GetInstance()->GetCurrWave() + 1;

		pFont->Draw(nWave.str().c_str(), textPos, 1.5f, { 155, 0, 0 });

		if (pAudio->IsAudioPlaying(Game::GetInstance()->m_hWaveChange) == false)
		{
			pAudio->PlayAudio(Game::GetInstance()->m_hWaveChange, false);
		}
	}

	else if (m_bShopState == false && SpawnManager::GetInstance()->GetEnemiesKilled() == SpawnManager::GetInstance()->GetNumWaveEnemies() && SpawnManager::GetInstance()->GetGameWon() == false)
	{
		stringstream nComplete;
		nComplete << "Wave " << SpawnManager::GetInstance()->GetCurrWave() + 1 << " Complete";

		pFont->Draw(nComplete.str().c_str(), textPos, 1.5f, { 155, 0, 0 });
	}

	else if (SpawnManager::GetInstance()->GetGameWon() == true)
	{
		stringstream gameWin;
		gameWin << "YOU WIN!";

		pFont->Draw(gameWin.str().c_str(), textPos, 1.5f, { 155, 0, 0 });


	}

	if (SpawnManager::GetInstance()->GetEnemiesKilled() == SpawnManager::GetInstance()->GetNumWaveEnemies())
	{

	}

	///////OLD Energy Bar & Stamina Bar Render///////
	/*
	pGraphics->DrawRectangle(energyRect, { 0, 0, 255 });

	SGD::Rectangle staminaRect = { lefts, tops, lefts + m_pPlayer->GetAttributes()->m_fCurrStamina / m_pPlayer->GetAttributes()->m_fMaxStamina * 150, tops + 25 };
	pGraphics->DrawRectangle(staminaRect, { 0, 255, 0 });
	*/

	stringstream moneyCount;
	if (m_bStoryMode == true)
	{
		moneyCount << "$" << Game::GetInstance()->GetStoryProfile().money;
	}
	else
		moneyCount << "$" << Game::GetInstance()->GetSurvivalProfile().money;

	
	pFont->Draw(moneyCount.str().c_str(), { 20, Game::GetInstance()->GetScreenHeight() - 75 }, 1.75f, { 0, 255, 0 });


	SGD::Point	retpos = { 0.0f, 0.0f };

	if (SGD::InputManager::GetInstance()->IsControllerConnected(0) == true)
	{
		retpos = { (player->GetPosition().x + (player->GetDirection().x * 300.0f)), (player->GetPosition().y + (player->GetDirection().y * 300.0f)) };
		retpos.Offset(-camera.GetPosition().x, -camera.GetPosition().y);
	}

	else
		retpos = SGD::InputManager::GetInstance()->GetMousePosition();
	
		


	float		retscale = 1.0f + (WeaponManager::GetInstance()->GetSelected()->GetRecoilTimer().GetTime());

	retpos.Offset((-11 * retscale)*0.5f, (-11 * retscale)*0.5f);
	pGraphics->DrawTexture(Game::GetInstance()->m_hReticleImage, retpos, 0.0F, {}, { 255, 255, 0 }, { retscale, retscale });

}

/**************************************************************/
// MessageProc
//	- process messages queued in the MessageManager
//	- STATIC METHOD
//		- does NOT have invoking object!!!
//		- must use singleton to access members
/*static*/ void GameplayState::MessageProc( const SGD::Message* pMsg )
{
/* Show warning when a Message ID enumerator is not handled */
#pragma warning( push )
#pragma warning( 1 : 4061 )

	// What type of message?
	switch( pMsg->GetMessageID() )
	{
		default:
		case MessageID::MSG_UNKNOWN:
		{
			OutputDebugStringW( L"Game::MessageProc - unknown message id\n" );
		}
		break;
	
	
		case MessageID::MSG_DESTROY_OBJECT:
		{
			const DestroyObjectMessage* pDestroyMsg = dynamic_cast<const DestroyObjectMessage*>(pMsg);
			assert(pDestroyMsg != nullptr && "Game::MessageProc - MSG_DESTROY_OBJECT is not actually a DestroyObjectMessage");

			BaseObject* ptr = pDestroyMsg->GetEntity();

			if (ptr->GetType() == BaseObject::OBJ_SLOW_ZOMBIE)
			{
				if (GameplayState::GetInstance()->GetGameMode() == true)
					Game::GetInstance()->GetStoryProfile().money += 20;
				else
					Game::GetInstance()->GetSurvivalProfile().money += 20;
			}

			else if (ptr->GetType() == BaseObject::OBJ_FAST_ZOMBIE)
			{
				if (GameplayState::GetInstance()->GetGameMode() == true)
					Game::GetInstance()->GetStoryProfile().money += 25;
				else
					Game::GetInstance()->GetSurvivalProfile().money += 25;
			}

			else if (ptr->GetType() == BaseObject::OBJ_EXPLODING_ZOMBIE)
			{
				if (GameplayState::GetInstance()->GetGameMode() == true)
					Game::GetInstance()->GetStoryProfile().money += 35;
				else
					Game::GetInstance()->GetSurvivalProfile().money += 35;
			}

			else if (ptr->GetType() == BaseObject::OBJ_FAT_ZOMBIE)
			{
				if (GameplayState::GetInstance()->GetGameMode() == true)
					Game::GetInstance()->GetStoryProfile().money += 75;
				else
					Game::GetInstance()->GetSurvivalProfile().money += 75;
			}

			else if (ptr->GetType() == BaseObject::OBJ_TANK_ZOMBIE)
			{
				if (GameplayState::GetInstance()->GetGameMode() == true)
					Game::GetInstance()->GetStoryProfile().money += 100;
				else
					Game::GetInstance()->GetSurvivalProfile().money += 100;
			}
			
			GameplayState::GetInstance()->m_pEntities->RemoveEntity(ptr);
		}
		break;


		case MessageID::MSG_CREATE_PSTL_BLT:
		{
			const CreatePistolBullet* pCreateBulletMsg = dynamic_cast<const CreatePistolBullet*>(pMsg);
			GameplayState::GetInstance()->CreateBullet(pCreateBulletMsg->GetOwner());
		}
		break;
		case MessageID::MSG_CREATE_SHTGN_BLT:
		{
			const CreateShotgunBullet* pCreateBulletMsg = dynamic_cast<const CreateShotgunBullet*>(pMsg);
			GameplayState::GetInstance()->CreateShotGunBullet(pCreateBulletMsg->GetOwner());
		}
		break;
		case MessageID::MSG_CREATE_ASSRFLE_BLT:
		{
			const CreateARifleBullet* pCreateBulletMsg = dynamic_cast<const CreateARifleBullet*>(pMsg);
			GameplayState::GetInstance()->CreateBullet(pCreateBulletMsg->GetOwner());
		}
		break;
		case MessageID::MSG_CREATE_SNPR_BLT:
		{
			const CreateSniperBullet* pCreateBulletMsg = dynamic_cast<const CreateSniperBullet*>(pMsg);
			GameplayState::GetInstance()->CreateSnipeBullet(pCreateBulletMsg->GetOwner());
		}
		break;
		case MessageID::MSG_CREATE_FLAME:
		{
			const CreateFlameBullet* pCreateBulletMsg = dynamic_cast<const CreateFlameBullet*>(pMsg);
			GameplayState::GetInstance()->CreateFireBullet(pCreateBulletMsg->GetOwner());
		}
		break;
		case MessageID::MSG_CREATE_PUKE:
		{
			const CreatePukeBullet* pCreateBulletMsg = dynamic_cast<const CreatePukeBullet*>(pMsg);
			GameplayState::GetInstance()->CreatePukeyBullet(pCreateBulletMsg->GetOwner());
		}
		break;
		case MessageID::MSG_CREATE_NADE:
		{
			const CreateGrenadeBullet* pCreateBulletMsg = dynamic_cast<const CreateGrenadeBullet*>(pMsg);
			GameplayState::GetInstance()->CreateGrenade(pCreateBulletMsg->GetOwner());
		}
		break;
		case MessageID::MSG_CREATE_SLOW_ZOMBIE:
		{
			const CreateZombieMessage* pCreateBulletMsg = dynamic_cast<const CreateZombieMessage*>(pMsg);
			GameplayState::GetInstance()->CreateZombie(pCreateBulletMsg->GetOwner());
		}
		break;
		case MessageID::MSG_CREATE_FAST_ZOMBIE:
		{
			const CreateFastZombieMsg* pCreateBulletMsg = dynamic_cast<const CreateFastZombieMsg*>(pMsg);
			GameplayState::GetInstance()->CreateFastZombie(pCreateBulletMsg->GetOwner());
		}
		break;
		case MessageID::MSG_CREATE_FAT_ZOMBIE:
		{
			const CreateFatZombieMsg* pCreateBulletMsg = dynamic_cast<const CreateFatZombieMsg*>(pMsg);
			GameplayState::GetInstance()->CreateFatZombie(pCreateBulletMsg->GetOwner());
		}
		break;
		case MessageID::MSG_CREATE_EXPLODING_ZOMBIE:
		{
			const CreateExplodingZombieMsg* pCreateBulletMsg = dynamic_cast<const CreateExplodingZombieMsg*>(pMsg);
			GameplayState::GetInstance()->CreateExplodingZombie(pCreateBulletMsg->GetOwner());
		}
		break;
		case MessageID::MSG_CREATE_TANK_ZOMBIE:
		{
			const CreateTankZombieMsg* pCreateBulletMsg = dynamic_cast<const CreateTankZombieMsg*>(pMsg);
			GameplayState::GetInstance()->CreateTankZombie(pCreateBulletMsg->GetOwner());
		}
		break;

		case MessageID::MSG_CREATE_TURRET:
		{
			const CreateTurretMessage* pCreateTurretMsg = dynamic_cast<const CreateTurretMessage*>(pMsg);
			GameplayState::GetInstance()->CreateTurret(pCreateTurretMsg->GetOwner());
		}
		break;
		
		case MessageID::MSG_CREATE_TURRET_BLT:
		{
			const CreateTurretBullet* pCreateBulletMsg = dynamic_cast<const CreateTurretBullet*>(pMsg);
			GameplayState::GetInstance()->CreateTurretBullets(pCreateBulletMsg->GetOwner());
		}
		break;

		case MessageID::MSG_CREATE_BLOOD:
		{
			const CreateBloodMsg* pCreateBloodMsg = dynamic_cast<const CreateBloodMsg*>(pMsg);
			GameplayState::GetInstance()->CreateBlood(pCreateBloodMsg->GetSpawnPos());
		}
		break;
	}

	

/* Restore previous warning levels */
#pragma warning( pop )

}


/**************************************************************/
// Factory Methods:
BaseObject* GameplayState::CreatePlayer( void )
{
	Player* player = new Player;
	player->SetPosition({ m_szWorldSize.width * .6f, m_szWorldSize.height * .6f });

	player->SetRotation(0.0f);
	player->SetMoveSpeed(180.0f);
	player->RetrieveBehavior("playerController");
	player->SetAnimation("player");
	if (m_bStoryMode == true)
		player->SetHealth(Game::GetInstance()->GetStoryProfile().health);
	else
		player->SetHealth(Game::GetInstance()->GetSurvivalProfile().health);

	
	return player;
}

void GameplayState::CreateTurret( MovingObject* owner )
{
	Turret* turret = new Turret;

	float		pixel_offset	= 100.0f;
	SGD::Vector	ownerpos		= { owner->GetPosition().x, owner->GetPosition().y };
	SGD::Vector	turretposV		= (owner->GetDirection() * pixel_offset) + ownerpos;
	SGD::Point	turretposP		= { turretposV.x, turretposV.y };

	turret->SetPosition(turretposP);
	turret->SetRotation(owner->GetRotation());
	turret->SetAnimation("turret");
	turret->RetrieveBehavior("hostile");

	turret->SetOwner(owner);

	m_pEntities->AddEntity(turret, EntityBucket::BUCKET_TURRETS);
	turret->Release();
	turret = nullptr;
}

void GameplayState::CreateBullet(Weapon* owner)
{
	Bullet* bullet = new Bullet;
	bullet->SetOwner(owner->GetOwner());
	bullet->SetPosition(owner->GetOwner()->GetPosition());
	SGD::Vector direction = owner->GetOwner()->GetDirection();
	float angle = ((rand() % (int)owner->GetBulletSpread() * 2) - (int)owner->GetBulletSpread()) *SGD::PI / 180.0f;
	
	direction.Rotate(angle);
	
	bullet->SetDirection(direction);
	bullet->SetRotation(owner->GetOwner()->GetRotation());
	bullet->SetDamage(owner->GetDamage());
	bullet->SetPenPower(owner->GetPenetratingPower());
	bullet->SetVelocity(direction * owner->GetSpeed());
	bullet->SetAnimation("bullet");
	
	m_pEntities->AddEntity(bullet, EntityBucket::BUCKET_BULLETS);
	bullet->Release();
	bullet = nullptr;
}
void GameplayState::CreateGrenade(Weapon* owner)
{

	Bullet* bullet = new Bullet;
	bullet->SetOwner(owner->GetOwner());
	bullet->SetPosition(owner->GetOwner()->GetPosition());
	SGD::Vector direction = owner->GetOwner()->GetDirection();

	bullet->SetDirection(direction);
	bullet->SetRotation(owner->GetOwner()->GetRotation());
	bullet->SetDamage(owner->GetDamage());

	bullet->SetVelocity(direction * owner->GetSpeed());
	bullet->SetAnimation("bullet");
	bullet->SetMoveSpeed(owner->GetSpeed());
	m_pEntities->AddEntity(bullet, EntityBucket::BUCKET_BULLETS);
	bullet->Release();
	bullet = nullptr;


}
void GameplayState::CreateFireBullet(Weapon* owner)
{
	
		Bullet* bullet = new Bullet;
		bullet->SetOwner(owner->GetOwner());
		bullet->SetPosition(owner->GetOwner()->GetPosition());
		SGD::Vector direction = owner->GetOwner()->GetDirection();
		float angle = ((rand() % (int)owner->GetBulletSpread() * 2) - (int)owner->GetBulletSpread()) *SGD::PI / 180.0f;

		direction.Rotate(angle);

		bullet->SetDirection(direction);
		bullet->SetRotation(owner->GetOwner()->GetRotation());

		bullet->SetVelocity(direction * owner->GetSpeed());
		bullet->SetAnimation("flameThrowerRound");
		bullet->SetDamage(owner->GetDamage());
		m_pEntities->AddEntity(bullet, EntityBucket::BUCKET_BULLETS);
		bullet->Release();
		bullet = nullptr;
	

}
void GameplayState::CreatePukeyBullet(Weapon* owner)
{

	Bullet* bullet = new Bullet;
	bullet->SetOwner(owner->GetOwner());
	bullet->SetPosition(owner->GetOwner()->GetPosition());
	SGD::Vector direction = owner->GetOwner()->GetDirection();
	float angle = ((rand() % (int)owner->GetBulletSpread() * 2) - (int)owner->GetBulletSpread()) *SGD::PI / 180.0f;

	direction.Rotate(angle);

	bullet->SetDirection(direction);
	bullet->SetRotation(owner->GetOwner()->GetRotation());
	bullet->SetType(BaseObject::ObjectType::OBJ_VOMIT);
	bullet->SetLifeTime(700.0f);
	bullet->SetVelocity(direction * owner->GetSpeed());
	bullet->SetAnimation("puke");
	bullet->SetDamage(owner->GetDamage());
	m_pEntities->AddEntity(bullet, EntityBucket::BUCKET_PUKE);
	bullet->Release();
	bullet = nullptr;


}
void GameplayState::CreateShotGunBullet(Weapon* owner)
{
	for (unsigned int i = 0; i < 10; i++)
	{
		Bullet* bullet = new Bullet;
		bullet->SetOwner(owner->GetOwner());
		bullet->SetPosition(owner->GetOwner()->GetPosition());
		SGD::Vector direction = owner->GetOwner()->GetDirection();
		float angle = ((rand() % (int)owner->GetBulletSpread() * 2) - (int)owner->GetBulletSpread()) *SGD::PI / 180.0f;

		direction.Rotate(angle);

		bullet->SetDirection(direction);
		bullet->SetRotation(owner->GetOwner()->GetRotation());
		bullet->SetDamage(owner->GetDamage());


		bullet->SetVelocity(direction * owner->GetSpeed());
		bullet->SetAnimation("bullet");

		m_pEntities->AddEntity(bullet, EntityBucket::BUCKET_BULLETS);
		bullet->Release();
		bullet = nullptr;
	}
}
void GameplayState::CreateARBullet(Weapon* owner)
{
	Bullet* bullet = new Bullet;
	bullet->SetRotation(owner->GetOwner()->GetRotation());
	bullet->SetOwner(owner->GetOwner());
	bullet->SetPosition(owner->GetOwner()->GetPosition());
	float angle = ((rand() % (int)owner->GetBulletSpread() * 2) - (int)owner->GetBulletSpread()) *SGD::PI / 180.0f;
	SGD::Vector direction = owner->GetOwner()->GetDirection();

	direction.Rotate(angle);

	
	bullet->SetDirection(direction);
	bullet->SetVelocity(direction * owner->GetSpeed());
	bullet->SetAnimation("bullet");
	bullet->SetDamage(owner->GetDamage());


	m_pEntities->AddEntity(bullet, EntityBucket::BUCKET_BULLETS);
	bullet->Release();
	bullet = nullptr;
}
void GameplayState::CreateSnipeBullet(Weapon* owner)
{
	Bullet* bullet = new Bullet;
	bullet->SetRotation(owner->GetOwner()->GetRotation());
	bullet->SetOwner(owner->GetOwner());
	bullet->SetPosition(owner->GetOwner()->GetPosition());
	float angle = ((rand() % (int)owner->GetBulletSpread() * 2) - (int)owner->GetBulletSpread()) *SGD::PI / 180.0f;
	SGD::Vector direction = owner->GetOwner()->GetDirection();

	direction.Rotate(angle);
	bullet->SetDamage(owner->GetDamage());
	bullet->SetDirection(direction);
	bullet->SetVelocity(direction * owner->GetSpeed());
	bullet->SetAnimation("bullet");
	bullet->SetDamage(owner->GetDamage());
	bullet->SetPenPower(owner->GetPenetratingPower());


	m_pEntities->AddEntity(bullet, EntityBucket::BUCKET_BULLETS);
	bullet->Release();
	bullet = nullptr;
}
void GameplayState::CreateTurretBullets(Turret* turret)
{
	Bullet* bullet = new Bullet;
	bullet->SetRotation(turret->GetRotation());
	bullet->SetOwner(turret);
	bullet->SetPosition(turret->GetPosition());
	SGD::Vector direction = turret->GetDirection();
	float angle = ((rand() % (int)turret->GetBulletSpread() * 2) - (int)turret->GetBulletSpread()) *SGD::PI / 180.0f;


	direction.Rotate(angle);
	
	bullet->SetDirection(direction);
	bullet->SetVelocity(direction * turret->GetSpeed());
	bullet->SetAnimation("bullet");
	bullet->SetDamage(turret->GetDamage());


	m_pEntities->AddEntity(bullet, EntityBucket::BUCKET_BULLETS);
	bullet->Release();
	bullet = nullptr;
}

void GameplayState::CreateZombie(Spawner* owner)
{
	Zombie* zombie = new Zombie;
	zombie->SetPosition(owner->GetPosition());
	zombie->SetRotation(0.0f);

	zombie->SetAnimation("slowZombie");
	zombie->SetMoveSpeed(64.0f);
	zombie->SetTarget(m_pPlayer);
	zombie->RetrieveBehavior("runTo");
	
	m_pEntities->AddEntity(zombie, EntityBucket::BUCKET_ENEMIES);
	zombie->Release();
	zombie = nullptr;
}
void GameplayState::CreateFatZombie(Spawner* owner)
{
	FatZombie* zombie = new FatZombie();
	zombie->SetPosition(owner->GetPosition());
	zombie->SetRotation(0.0f);

	zombie->SetAnimation("fatZombie");
	zombie->SetMoveSpeed(32.0f);
	zombie->SetTarget(m_pPlayer);
	zombie->RetrieveBehavior("runTo");

	m_pEntities->AddEntity(zombie, EntityBucket::BUCKET_ENEMIES);
	zombie->Release();
	zombie = nullptr;
}
void GameplayState::CreateFastZombie(Spawner* owner)
{
	FastZombie* zombie = new FastZombie;
	zombie->SetPosition(owner->GetPosition());
	zombie->SetRotation(0.0f);
	
	zombie->SetAnimation("fastZombie");
	zombie->SetMoveSpeed(96.0f);
	zombie->SetTarget(m_pPlayer);
	zombie->RetrieveBehavior("runTo");

	m_pEntities->AddEntity(zombie, EntityBucket::BUCKET_ENEMIES);
	zombie->Release();
	zombie = nullptr;
}

void GameplayState::CreateExplodingZombie(Spawner* owner)
{
	ExplodingZombie* zombie = new ExplodingZombie();
	zombie->SetPosition(owner->GetPosition());
	zombie->SetRotation(0.0f);

	zombie->SetAnimation("explodingZombie");
	zombie->SetMoveSpeed(64.0f);
	zombie->SetTarget(m_pPlayer);
	zombie->RetrieveBehavior("runTo");

	m_pEntities->AddEntity(zombie, EntityBucket::BUCKET_ENEMIES);
	zombie->Release();
	zombie = nullptr;
}
void GameplayState::CreateTankZombie(Spawner* owner)
{
	TankZombie* zombie = new TankZombie;
	zombie->SetPosition(owner->GetPosition());
	zombie->SetRotation(0.0f);
	zombie->SetAnimation("tankZombie");
	zombie->SetMoveSpeed(32.0f);
	zombie->SetTarget(m_pPlayer);
	zombie->RetrieveBehavior("runTo");

	m_pEntities->AddEntity(zombie, EntityBucket::BUCKET_ENEMIES);
	zombie->Release();
	zombie = nullptr;
}
void GameplayState::UpdateWeaponManager()
{
	GamerProfile profile;

	WeaponManager* m_pWeapons = WeaponManager::GetInstance();
	if (GameplayState::GetInstance()->GetGameMode())
		profile = Game::GetInstance()->GetStoryProfile();
	else
		profile = Game::GetInstance()->GetSurvivalProfile();


	m_pWeapons->GetWeapons()[GLOCK]->SetReloadTime(profile.pistol.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[GLOCK]->SetRecoilTime(profile.pistol.recoilTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[GLOCK]->SetMagSize(profile.pistol.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[GLOCK]->SetEquipped(profile.pistol.isEquipt);

	m_pWeapons->GetWeapons()[REVOLVER]->SetReloadTime(profile.revolver.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[REVOLVER]->SetRecoilTime(profile.revolver.recoilTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[REVOLVER]->SetMagSize(profile.revolver.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[REVOLVER]->SetDamage(profile.revolver.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[REVOLVER]->SetPenPower(profile.revolver.penPower.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[REVOLVER]->SetTotalAmmo(profile.revolver.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[REVOLVER]->SetAmmoCap(profile.revolver.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[REVOLVER]->SetObtained(profile.revolver.isBought);
	m_pWeapons->GetWeapons()[REVOLVER]->SetEquipped(profile.revolver.isEquipt);



	m_pWeapons->GetWeapons()[MAC10]->SetReloadTime(profile.mac10.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[MAC10]->SetRecoilTime(0.2f);

	m_pWeapons->GetWeapons()[MAC10]->SetMagSize(profile.mac10.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[MAC10]->SetDamage(profile.mac10.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[MAC10]->SetBulletSpread(profile.mac10.bulletSpread.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[MAC10]->SetTotalAmmo(profile.mac10.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[MAC10]->SetAmmoCap(profile.mac10.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[MAC10]->SetObtained(profile.mac10.isBought);
	m_pWeapons->GetWeapons()[MAC10]->SetEquipped(profile.mac10.isEquipt);


	m_pWeapons->GetWeapons()[TECH9]->SetReloadTime(profile.tech9.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[TECH9]->SetMagSize(profile.tech9.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[TECH9]->SetDamage(profile.tech9.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[TECH9]->SetBulletSpread(profile.tech9.bulletSpread.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[TECH9]->SetTotalAmmo(profile.tech9.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[TECH9]->SetAmmoCap(profile.tech9.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[TECH9]->SetRecoilTime(0.3f);
	m_pWeapons->GetWeapons()[TECH9]->SetObtained(profile.tech9.isBought);
	m_pWeapons->GetWeapons()[TECH9]->SetEquipped(profile.tech9.isEquipt);

	m_pWeapons->GetWeapons()[SP90]->SetReloadTime(profile.p90.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SP90]->SetMagSize(profile.p90.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SP90]->SetDamage(profile.p90.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SP90]->SetBulletSpread(profile.p90.bulletSpread.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SP90]->SetTotalAmmo(profile.p90.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SP90]->SetAmmoCap(profile.p90.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SP90]->SetRecoilTime(0.1f);
	m_pWeapons->GetWeapons()[SP90]->SetObtained(profile.p90.isBought);
	m_pWeapons->GetWeapons()[SP90]->SetEquipped(profile.p90.isEquipt);


	m_pWeapons->GetWeapons()[SAWN]->SetReloadTime(profile.sawnoff.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SAWN]->SetRecoilTime(profile.sawnoff.recoilTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SAWN]->SetDamage(profile.sawnoff.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SAWN]->SetBulletSpread(profile.sawnoff.bulletSpread.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SAWN]->SetTotalAmmo(profile.sawnoff.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SAWN]->SetAmmoCap(profile.sawnoff.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SAWN]->SetObtained(profile.sawnoff.isBought);
	m_pWeapons->GetWeapons()[SAWN]->SetEquipped(profile.sawnoff.isEquipt);

	m_pWeapons->GetWeapons()[PUMP]->SetReloadTime(profile.pumpShotgun.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[PUMP]->SetRecoilTime(profile.pumpShotgun.recoilTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[PUMP]->SetDamage(profile.pumpShotgun.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[PUMP]->SetBulletSpread(profile.pumpShotgun.bulletSpread.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[PUMP]->SetTotalAmmo(profile.pumpShotgun.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[PUMP]->SetAmmoCap(profile.pumpShotgun.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[PUMP]->SetMagSize(profile.pumpShotgun.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[PUMP]->SetObtained(profile.pumpShotgun.isBought);
	m_pWeapons->GetWeapons()[PUMP]->SetEquipped(profile.pumpShotgun.isEquipt);


	m_pWeapons->GetWeapons()[AUTO]->SetReloadTime(profile.autoShotgun.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AUTO]->SetRecoilTime(profile.autoShotgun.recoilTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AUTO]->SetDamage(profile.autoShotgun.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AUTO]->SetBulletSpread(profile.autoShotgun.bulletSpread.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AUTO]->SetTotalAmmo(profile.autoShotgun.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AUTO]->SetAmmoCap(profile.autoShotgun.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AUTO]->SetMagSize(profile.autoShotgun.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AUTO]->SetObtained(profile.autoShotgun.isBought);
	m_pWeapons->GetWeapons()[AUTO]->SetEquipped(profile.autoShotgun.isEquipt);


	m_pWeapons->GetWeapons()[AK47]->SetReloadTime(profile.ak47.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AK47]->SetRecoilTime(profile.ak47.recoilTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AK47]->SetDamage(profile.ak47.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AK47]->SetBulletSpread(profile.ak47.bulletSpread.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AK47]->SetTotalAmmo(profile.ak47.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AK47]->SetAmmoCap(profile.ak47.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AK47]->SetMagSize(profile.ak47.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[AK47]->SetObtained(profile.ak47.isBought);
	m_pWeapons->GetWeapons()[AK47]->SetEquipped(profile.ak47.isEquipt);


	m_pWeapons->GetWeapons()[M16]->SetReloadTime(profile.m16.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[M16]->SetRecoilTime(profile.m16.recoilTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[M16]->SetDamage(profile.m16.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[M16]->SetBulletSpread(profile.m16.bulletSpread.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[M16]->SetTotalAmmo(profile.m16.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[M16]->SetAmmoCap(profile.m16.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[M16]->SetMagSize(profile.m16.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[M16]->SetObtained(profile.m16.isBought);
	m_pWeapons->GetWeapons()[M16]->SetEquipped(profile.m16.isEquipt);


	m_pWeapons->GetWeapons()[LIGHT_MG]->SetReloadTime(profile.lmg.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[LIGHT_MG]->SetRecoilTime(profile.lmg.recoilTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[LIGHT_MG]->SetDamage(profile.lmg.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[LIGHT_MG]->SetBulletSpread(profile.lmg.bulletSpread.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[LIGHT_MG]->SetTotalAmmo(profile.lmg.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[LIGHT_MG]->SetAmmoCap(profile.lmg.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[LIGHT_MG]->SetMagSize(profile.lmg.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[LIGHT_MG]->SetObtained(profile.lmg.isBought);
	m_pWeapons->GetWeapons()[LIGHT_MG]->SetEquipped(profile.lmg.isEquipt);


	m_pWeapons->GetWeapons()[FTHROWER]->SetReloadTime(profile.flameThrower.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[FTHROWER]->SetDamage(profile.flameThrower.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[FTHROWER]->SetBulletSpread(profile.flameThrower.bulletSpread.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[FTHROWER]->SetSpeed(profile.flameThrower.bulletVelocity.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[FTHROWER]->SetTotalAmmo(profile.flameThrower.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[FTHROWER]->SetAmmoCap(profile.flameThrower.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[FTHROWER]->SetMagSize(profile.flameThrower.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[FTHROWER]->SetObtained(profile.flameThrower.isBought);
	m_pWeapons->GetWeapons()[FTHROWER]->SetEquipped(profile.flameThrower.isEquipt);


	m_pWeapons->GetWeapons()[GLAUNCHER]->SetReloadTime(profile.nadeLauncher.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[GLAUNCHER]->SetDamage(profile.nadeLauncher.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[GLAUNCHER]->SetSpeed(profile.nadeLauncher.bulletVelocity.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[GLAUNCHER]->SetTotalAmmo(profile.nadeLauncher.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[GLAUNCHER]->SetAmmoCap(profile.nadeLauncher.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[GLAUNCHER]->SetMagSize(profile.nadeLauncher.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[GLAUNCHER]->SetObtained(profile.nadeLauncher.isBought);
	m_pWeapons->GetWeapons()[GLAUNCHER]->SetEquipped(profile.nadeLauncher.isEquipt);

	m_pWeapons->GetWeapons()[SNIPER]->SetReloadTime(profile.sniper.reloadTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SNIPER]->SetRecoilTime(profile.sniper.recoilTime.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SNIPER]->SetPenPower(profile.sniper.penPower.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SNIPER]->SetDamage(profile.sniper.damage.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SNIPER]->SetTotalAmmo(profile.sniper.totalAmmo.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SNIPER]->SetAmmoCap(profile.sniper.ammoCap.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SNIPER]->SetMagSize(profile.sniper.magSize.upgradedSkill.stat);
	m_pWeapons->GetWeapons()[SNIPER]->SetObtained(profile.sniper.isBought);
	m_pWeapons->GetWeapons()[SNIPER]->SetEquipped(profile.sniper.isEquipt);

}

void GameplayState::CreateBlood(SGD::Point pos)
{
	BloodSplatter* blood = new BloodSplatter;
	blood->SetPosition(pos);

	unsigned int choice = rand() % 4;

	switch (choice)
	{
	case 0:
		blood->SetAnimation("blood1");
		break;
	case 1:
		blood->SetAnimation("blood2");
		break;
	case 2:
		blood->SetAnimation("blood3");
		break;
	case 3:
		blood->SetAnimation("blood4");
		break;
	}

	m_pEntities->AddEntity(blood, EntityBucket::BUCKET_BLOOD);
	blood->Release();
	blood = nullptr;
}
