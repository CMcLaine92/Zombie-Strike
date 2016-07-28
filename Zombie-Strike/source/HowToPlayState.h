#pragma once

#include "IGameState.h"

class HowToPlayState : public IGameState
{
public:
	/**********************************************************/
	// Singleton Accessor
	static HowToPlayState* GetInstance(void);

	
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
	HowToPlayState( void )			= default;
	virtual ~HowToPlayState( void )	= default;

	HowToPlayState( const HowToPlayState& )				= delete;	
	HowToPlayState& operator= ( const HowToPlayState& )	= delete;



};

