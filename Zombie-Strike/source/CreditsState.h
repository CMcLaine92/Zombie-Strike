#pragma once

#include "IGameState.h"
#include "../SGD Wrappers/SGD_Handle.h"			// uses HTexture & HAudio

class CreditsState : public IGameState
{
public:
	/**********************************************************/
	// Singleton Accessor
	static CreditsState* GetInstance( void );

	
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
	CreditsState( void )			= default;
	virtual ~CreditsState( void )	= default;

	CreditsState( const CreditsState& )				= delete;	
	CreditsState& operator= ( const CreditsState& )	= delete;



	/**********************************************************/
	// Setup & workings
	float			starting_y			= 170.0F;


};

