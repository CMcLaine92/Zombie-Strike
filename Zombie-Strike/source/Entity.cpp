/***************************************************************
|	File:		Entity.cpp
|	Author:		Jason Bloomfield
|	Course:		N/A
|	Purpose:	Entity class stores the shared data members
|				for all child game entities
***************************************************************/

#include "Entity.h"

#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <cassert>


/**************************************************************/
// DESTRUCTOR
/*virtual*/ Entity::~Entity( void )
{
	assert( m_unRefCount == 0 && "~Entity - entity was destroyed while references remain!" );
}


/**************************************************************/
// Update
//	- move the entity's position by its velocity
/*virtual*/ void Entity::Update( float elapsedTime )
{
	m_ptPosition += m_vtVelocity * elapsedTime;
}


/**************************************************************/
// Render
//	- draw the entity's image at its position
/*virtual*/ void Entity::Render( void )
{
	// Verify the image
	assert( m_hImage != SGD::INVALID_HANDLE && "Entity::Render - image was not set!" );
	

	// Draw the image
	SGD::GraphicsManager::GetInstance()->DrawTexture( 
		m_hImage, m_ptPosition,
		m_fRotation, m_szSize/2 );
}


/**************************************************************/
// GetRect
//	- calculate the entity's bounding rectangle
/*virtual*/ SGD::Rectangle Entity::GetRect( void ) const
{
	return SGD::Rectangle{ m_ptPosition, m_szSize };
}


/**************************************************************/
// HandleCollision
//	- respond to collision between entities
/*virtual*/ void Entity::HandleCollision( const IEntity* pOther )
{
	/* DO NOTHING */
	(void)pOther;		// unused parameter
}


/**************************************************************/
// AddRef
//	- increase the reference count
/*virtual*/ void Entity::AddRef( void )
{
	assert( m_unRefCount != 0xFFFFFFFF && "Entity::AddRef - maximum reference count has been exceeded" );

	++m_unRefCount;
}


/**************************************************************/
// Release
//	- decrease the reference count
//	- self-destruct when the count is 0
/*virtual*/ void Entity::Release( void )
{
	--m_unRefCount;

	if( m_unRefCount == 0 )
		delete this;
}
