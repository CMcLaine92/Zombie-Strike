#pragma once

#include "IGameState.h"
#include "../SGD Wrappers/SGD_Handle.h"			// uses HTexture & HAudio

class OptionsState : public IGameState
{
public:
	/**********************************************************/
	// Singleton Accessor
	static OptionsState* GetInstance(void);

	
	/**********************************************************/
	// IGameState Interface:
	virtual void	Enter( void )				override;	// load resources
	virtual void	Exit ( void )				override;	// unload resources

	virtual bool	Input( void )				override;	// handle user input
	virtual void	Update( float elapsedTime )	override;	// update entites
	virtual void	Render( void )				override;	// render entities / menu
	

	/**********************************************************/
	// Other Methods:
	void			LoadVolumes	( void )	const;
	void			SaveVolumes	( void )	const;


private:
	/**********************************************************/
	// SINGLETON!
	OptionsState( void )			= default;
	virtual ~OptionsState( void )	= default;

	OptionsState( const OptionsState& )				= delete;	
	OptionsState& operator= ( const OptionsState& )	= delete;



	/**********************************************************/
	// Cursor Index
	int				m_nCursor = 0;
	bool			m_bFullScreen			= false;


	/**********************************************************/
	// Assets
	SGD::HAudio		m_hBackgroundSFX = SGD::INVALID_HANDLE;
};

