/***************************************************************
|	File:		EntityManager.h
|	Author:		Jason Bloomfield
|	Course:		N/A
|	Purpose:	EntityManager class stores & maintains all game entities
***************************************************************/

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


class IBase;			// uses IBase*
#include <vector>		// uses std::vector


/**************************************************************/
// EntityManager class
//	- stores references to game entities
//	- updates & renders all game entities
class EntityManager
{
public:
	/**********************************************************/
	// Default constructor & destructor
	EntityManager( void )	= default;
	~EntityManager( void )	= default;
	

	/**********************************************************/
	// Entity Storage:
	void	AddEntity	( IBase* pEntity, unsigned int bucket );
	void	RemoveEntity( IBase* pEntity, unsigned int bucket );
	void	RemoveEntity( IBase* pEntity );
	void	RemoveAll	( unsigned int bucket );
	void	RemoveAll	( void );
	

	/**********************************************************/
	// Entity Upkeep:
	void	UpdateAll	( float elapsedTime );
	void	RenderAll	( void );

	void	CheckCollisions( unsigned int bucket1, unsigned int bucket2 );


private:
	/**********************************************************/
	// Not a singleton, but still don't want the Trilogy-of-Evil
	EntityManager( const EntityManager& )				= delete;
	EntityManager& operator= ( const EntityManager& )	= delete;

	
	/**********************************************************/
	// Typedefs will simplify the templates
	typedef std::vector< IBase* >		EntityVector;
	typedef std::vector< EntityVector >	EntityTable;
	
	/**********************************************************/
	// members:
	EntityTable	m_tEntities;			// vector-of-vector-of-IBase* (2D table)
	bool		m_bIterating = false;	// read/write lock
};

#endif //ENTITYMANAGER_H
