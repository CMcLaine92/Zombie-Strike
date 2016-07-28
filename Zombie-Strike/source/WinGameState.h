#pragma once

#include "IGameState.h"
#include "../SGD Wrappers/SGD_Handle.h"			// uses HTexture & HAudio

class WinGameState : public IGameState
{
public:
	/**********************************************************/
	// Singleton Accessor
	static WinGameState* GetInstance( void );

	
	/**********************************************************/
	// IGameState Interface:
	virtual void	Enter( void )				override;	// load resources
	virtual void	Exit ( void )				override;	// unload resources

	virtual bool	Input( void )				override;	// handle user input
	virtual void	Update( float elapsedTime )	override;	// update entites
	virtual void	Render( void )				override;	// render entities / menu


private:
	/**********************************************************/
	// SINGLETON!
	WinGameState( void )			= default;
	virtual ~WinGameState( void )	= default;

	WinGameState( const WinGameState& )				= delete;	
	WinGameState& operator= ( const WinGameState& )	= delete;



	/**********************************************************/
	// Cursor Index
	int		m_nCursor		= 0;



	/**********************************************************/
	// Assets
	SGD::HTexture	m_hBackgroundImage	= SGD::INVALID_HANDLE;

};

