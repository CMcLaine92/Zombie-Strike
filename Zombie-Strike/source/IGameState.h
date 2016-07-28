#pragma once

enum class StateType{ GPLAY, MENU, HTP, OPTIONS, CREDITS, PAUSE };

/**************************************************************/
// IGameState class
//	- abstract base class!
//	- declares interface for game state
class IGameState
{
protected:
	/**********************************************************/
	// Virtual Destructor
	IGameState( void )			= default;
	virtual ~IGameState( void )	= default;


public:
	/**********************************************************/
	// IGameState Interface:
	virtual void	Enter( void )				= 0;	// load resources
	virtual void	Exit ( void )				= 0;	// unload resources

	virtual bool	Input( void )				= 0;	// handle user input
	virtual void	Update( float elapsedTime )	= 0;	// update entites
	virtual void	Render( void )				= 0;	// render entities / menu


	
	virtual StateType	GetType	( void )			{ return m_stStateType; }
	virtual void		SetType	( StateType sType )	{ m_stStateType = sType; }


private:

	StateType		m_stStateType;

};

