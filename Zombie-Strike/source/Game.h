#ifndef GAME_H
#define GAME_H

//#include "StateMachine.h"
#include <stack>
#include "GamerProfile.h"
#include "../SGD Wrappers/SGD_Handle.h"

/**************************************************************/
// Forward class declaration
//	- tells the compiler that the type exists
//	- allows us to create pointers or references
class BitmapFont;
class IGameState;
class MainMenuState;
class GameplayState;
class HowToPlayState;
class CreditsState;
class OptionsState;


/**************************************************************/
// Game class
//	- runs the game logic
//	- controls the SGD wrappers
//	- SINGLETON!
//		- there is only ONE instance
//		- global access method (GetInstance)
class Game
{
public:
	/**********************************************************/
	// Singleton Accessors:
	static Game*	GetInstance		( void );
	static void		DeleteInstance	( void );

	
	/**********************************************************/
	// Setup, Play, Cleanup:
	bool Initialize	( float width, float height, const wchar_t* title );
	int	 Update		( void );
	void Terminate	( void );
	
	
	/**********************************************************/
	// Screen Size Accessors:
	float				GetScreenWidth	( void ) const	{	return m_fScreenWidth;	}
	float				GetScreenHeight ( void ) const	{	return m_fScreenHeight;	} 


	/**********************************************************/
	// Font Accessor: (#include "BitmapFont.h" to use!)
	const BitmapFont*	GetFont			( void ) const	{	return m_pFont;			}
	const BitmapFont*	GetShopFont(void) const	{ return m_pFont2; }


	/**********************************************************/
	// Delta time
	float				DeltaTime		( void ) const { return elapsedTime; }


	/**********************************************************/
	// Gamer profile
	GamerProfile&		GetStoryProfile		( void )		{	return storyProfiles[selectedProfile];	}
	GamerProfile&		GetSurvivalProfile(void)		{ return survivalProfiles[selectedProfile]; }

	GamerProfile&		GetTutorialProfile(void)		{ return tutorialProfile; }




	GamerProfile&		GetSpecStoryProfile(int index)		{ return storyProfiles[index]; }
	GamerProfile&		GetSpecSurvialProfile(int index)		{ return survivalProfiles[index]; }

	void				LoadStoryProfiles	( void );
	void				LoadSurvivalProfiles(void);
	void				LoadTutorialProfiles(void);


	void				CreateStoryProfiles	( void );
	void				CreateSurvivalProfiles(void);
	void				CreateTutorialProfile(void);

	void				OverWriteProfile(GamerProfile& profile);



	unsigned int		selectedProfile	= 0;

	IGameState* GetCurrState() const { return m_pCurrState; }

	/**********************************************************/
	// Music
	SGD::HAudio			m_hMainTheme		= SGD::INVALID_HANDLE;
	SGD::HAudio			m_hSurvivalTheme	= SGD::INVALID_HANDLE;

	SGD::HAudio			turret_good	= SGD::INVALID_HANDLE;
	SGD::HAudio			turret_bad	= SGD::INVALID_HANDLE;
	SGD::HAudio playerDeath			= SGD::INVALID_HANDLE;
	SGD::HAudio playerHurt1			= SGD::INVALID_HANDLE;
	SGD::HAudio playerHurt2			= SGD::INVALID_HANDLE;
	SGD::HAudio playerHurt3			= SGD::INVALID_HANDLE;
	SGD::HAudio cannot_use_skill	= SGD::INVALID_HANDLE;
	SGD::HAudio footstep			= SGD::INVALID_HANDLE;
	SGD::HAudio zombie_pain			= SGD::INVALID_HANDLE;
	SGD::HAudio bullet_hit_zombie	= SGD::INVALID_HANDLE;
	SGD::HAudio bullet_hit_house	= SGD::INVALID_HANDLE;
	SGD::HAudio out_of_ammo			= SGD::INVALID_HANDLE;
	SGD::HAudio reload_begin		= SGD::INVALID_HANDLE;
	SGD::HAudio reload_finish		= SGD::INVALID_HANDLE;
	SGD::HAudio explosion			= SGD::INVALID_HANDLE;
	SGD::HAudio vomit_hit_player	= SGD::INVALID_HANDLE;
	SGD::HAudio pistol_fire			= SGD::INVALID_HANDLE;
	SGD::HAudio shotgun_fire		= SGD::INVALID_HANDLE;
	SGD::HAudio rifle_fire			= SGD::INVALID_HANDLE;
	SGD::HAudio sniper_fire			= SGD::INVALID_HANDLE;
	SGD::HAudio flamethrower_fire	= SGD::INVALID_HANDLE;
	SGD::HAudio smg_fire			= SGD::INVALID_HANDLE;
	SGD::HAudio rpg_fire			= SGD::INVALID_HANDLE;
	SGD::HAudio vomit_fire			= SGD::INVALID_HANDLE;
	SGD::HAudio storyMusic			= SGD::INVALID_HANDLE;
	SGD::HAudio m_hWpnSwitch		= SGD::INVALID_HANDLE;
	SGD::HAudio m_hWaveChange		= SGD::INVALID_HANDLE;
	SGD::HAudio zombie_hit_house1	= SGD::INVALID_HANDLE;
	SGD::HAudio zombie_hit_house2	= SGD::INVALID_HANDLE;



	/**********************************************************/
	// Game State Machine:
	//	- can ONLY be called by the state's Input, Update, or Render methods!!!
	void				AddState		( IGameState* pNewState );
	void				RemoveState		( void );

	SGD::HTexture m_hHudWpn = SGD::INVALID_HANDLE;
	SGD::HTexture m_hReticleImage = SGD::INVALID_HANDLE;

	bool isActive = true;


private:
	/**********************************************************/
	// Singleton Object:
	static Game*	s_pInstance;

	Game( void )	= default;		// default constructor
	~Game( void )	= default;		// destructor

	Game( const Game& )				= delete;	// copy constructor
	Game& operator= ( const Game& )	= delete;	// assignment operator

	

	/**********************************************************/
	// Screen Size
	float					m_fScreenWidth	= 1;
	float					m_fScreenHeight = 1;
	

	/**********************************************************/
	// Game title
	const wchar_t*			m_strGameTitle	= L"untitled";


	/**********************************************************/
	// Game Font
	BitmapFont*				m_pFont			= nullptr;
	BitmapFont*				m_pFont2		= nullptr;



	/**********************************************************/
	// Current Game State
	IGameState*				m_pCurrState	= nullptr;
	std::stack<IGameState*>	stateMachine;


	/**********************************************************/
	// Game Time
	unsigned long			m_ulGameTime	= 0;
	float					elapsedTime		= 0.0f;


	/**********************************************************/
	// Gamer profile


	/**********************************************************/
	// Loading screen
	SGD::HTexture			loadScreen		= SGD::INVALID_HANDLE;

	GamerProfile		storyProfiles[3];
	GamerProfile		survivalProfiles[3];
	GamerProfile		tutorialProfile;
};

#endif //GAME_H
