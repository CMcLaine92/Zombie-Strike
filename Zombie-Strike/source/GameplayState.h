#pragma once

#include "IGameState.h"							// uses IGameState
#include "../SGD Wrappers/SGD_Handle.h"			// uses HTexture & HAudio
#include "../SGD Wrappers/SGD_Declarations.h"	// uses Message
#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_String.h"
#include "GameCamera.h"
#include "MapManager.h"
#include "Timer.h"

/**************************************************************/
// Forward class declaration
class BaseObject;
class MovingObject;
class Weapon;
class Spawner;
class EntityManager;
class BehaviorManager;
class AnimationManager;
class SandBag;
class LandMine;
class BarbedWire;
class Turret;

/**************************************************************/
// GameplayState class
//	- runs the game logic
//	- SINGLETON! (Static allocation, not dynamic)
class GameplayState : public IGameState
{
public:
	/**********************************************************/
	// Singleton Accessor:
	static GameplayState* GetInstance( void );

	/**********************************************************/
	// IGameState Interface:
	

	virtual void	Enter	( void )		override;	// load resources
	virtual void	Exit	( void )		override;	// unload resources
													
	virtual bool	Input	( void )		override;	// handle user input
	virtual void	Update	( float dt )	override;	// update game entities / animations
	virtual void	Render	( void )		override;	// render game entities / menus


	/**********************************************************/
	// Other Methods:
	GameCamera*		GetCamera		( void )	{ return &camera; }
	SGD::Size		GetWorldSize	( void )	{ return m_szWorldSize; }
	void			PauseAudio		( bool );

	// true/false == story/survival
	bool			GetGameMode		( void ) const	{ return m_bStoryMode; }
	void			SetGameMode		( bool m )		{ m_bStoryMode = m; }


	bool GetShopState() const { return m_bShopState; }
	Timer GetWaveTimer() const { return m_tNextWave; }
	Timer GetWaveEndTimer() const { return m_tCompleteWave; }

	void SetShopState(bool shopState) { m_bShopState = shopState; }
	void SetWaveTimer(Timer nwave) { m_tNextWave = nwave; }

	/**********************************************************/
	// Factory Methods:
	BaseObject*		CreatePlayer	( void );
	void			CreateZombie	(Spawner* owner );
	void			CreateFatZombie(Spawner* owner);
	void			CreateFastZombie(Spawner* owner);
	void			CreateExplodingZombie(Spawner* owner);
	void			CreateTankZombie(Spawner* owner);
	void			CreatePickUp	( int type, SGD::Point pos );
	void			CreateTurret	( MovingObject* owner );
	void			CreateBullet	( Weapon* owner );
	void			CreateShotGunBullet	(Weapon* owner);
	void			CreateARBullet	(Weapon* owner);
	void			CreateSnipeBullet	(Weapon* owner);
	void			CreateFireBullet(Weapon* owner);
	void			CreatePukeyBullet(Weapon* owner);
	void			CreateTurretBullets(Turret* turret);
	void			CreateBlood(SGD::Point pos);

	void			CreateGrenade(Weapon* owner);
	BaseObject*		GetPlayer() const { return m_pPlayer; }

	



	/**********************************************************/
	// Assets
	//SGD::HAudio playerDeath			= SGD::INVALID_HANDLE;
	//SGD::HAudio playerHurt1			= SGD::INVALID_HANDLE;
	//SGD::HAudio playerHurt2			= SGD::INVALID_HANDLE;
	//SGD::HAudio playerHurt3			= SGD::INVALID_HANDLE;
	//SGD::HAudio cannot_use_skill	= SGD::INVALID_HANDLE;
	//SGD::HAudio footstep			= SGD::INVALID_HANDLE;
	//SGD::HAudio turretfire			= SGD::INVALID_HANDLE;
	//SGD::HAudio m_hWpnSwitch		= SGD::INVALID_HANDLE;
	//SGD::HAudio m_hWaveChange = SGD::INVALID_HANDLE;
	//
	//SGD::HTexture m_hHudWpn = SGD::INVALID_HANDLE;
	//SGD::HAudio storyMusic			= SGD::INVALID_HANDLE;
	SGD::HAudio survivalMusic		= SGD::INVALID_HANDLE;
	//SGD::HAudio zombie_pain			= SGD::INVALID_HANDLE;
	//SGD::HAudio bullet_hit_zombie	= SGD::INVALID_HANDLE;
	//SGD::HAudio bullet_hit_house	= SGD::INVALID_HANDLE;
	//SGD::HAudio out_of_ammo			= SGD::INVALID_HANDLE;
	//SGD::HAudio reload_begin		= SGD::INVALID_HANDLE;
	//SGD::HAudio reload_finish		= SGD::INVALID_HANDLE;
	//SGD::HAudio explosion			= SGD::INVALID_HANDLE;
	//SGD::HAudio vomit_hit_player	= SGD::INVALID_HANDLE;
	//
	//SGD::HAudio pistol_fire			= SGD::INVALID_HANDLE;
	//SGD::HAudio shotgun_fire		= SGD::INVALID_HANDLE;
	//SGD::HAudio rifle_fire			= SGD::INVALID_HANDLE;
	//SGD::HAudio sniper_fire			= SGD::INVALID_HANDLE;
	//SGD::HAudio flamethrower_fire	= SGD::INVALID_HANDLE;
	//SGD::HAudio smg_fire			= SGD::INVALID_HANDLE;
	//SGD::HAudio rpg_fire			= SGD::INVALID_HANDLE;
	//SGD::HAudio vomit_fire			= SGD::INVALID_HANDLE;

	//SGD::HAudio * m_hMain = nullptr;
	//SGD::HAudio * m_hSurvive = nullptr;



private:
	/**********************************************************/
	// SINGLETON (not-dynamically allocated)
	GameplayState( void ) = default;	// default constructor
	virtual ~GameplayState( void) = default;	// destructor

	GameplayState( const GameplayState& )				= delete;	// copy constructor
	GameplayState& operator= ( const GameplayState& )	= delete;	// assignment operator


	/**********************************************************/
	// Message Callback Function:
	static void MessageProc( const SGD::Message* pMsg );

	void UpdateWeaponManager();




	/**********************************************************/
	// Game Entities
	enum EntityBucket { BUCKET_BLOOD, BUCKET_PLAYER, BUCKET_ENEMIES, BUCKET_ENVIRO, BUCKET_TURRETS, BUCKET_BULLETS, BUCKET_PUKE, BUCKET_COLLIDABLE, BUCKET_PICKUPS };
	enum Gun { GLOCK, REVOLVER, SAWN, PUMP, AUTO, MAC10, TECH9, SP90, M16, LIGHT_MG, AK47, SNIPER, FTHROWER, GLAUNCHER };

	EntityManager*			m_pEntities			= nullptr;
	AnimationManager*		m_pAnimManager		= nullptr;




	//BaseObject*				m_pPlayer			= nullptr;
	BaseObject*					m_pPlayer			= nullptr;
	GameCamera				camera;


	/**********************************************************/
	// World size
	SGD::Size				m_szWorldSize		= { 2080, 2080 };


	//Textures
	//SGD::HTexture	m_hReticleImage = SGD::INVALID_HANDLE;



	/**********************************************************/
	// Game mode: Story/Survival
	bool					m_bStoryMode		= true;

	bool m_bShopState = false;

	Timer m_tNextWave;
	Timer m_tCompleteWave;
	Timer m_tStartWave;

	Timer m_tToWinState;

};
