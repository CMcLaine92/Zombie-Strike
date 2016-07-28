#pragma once

#include "SandBag.h"

class BarbedWire : public SandBag
{
protected:

	float	m_fDamage;


public:
	BarbedWire();
	~BarbedWire();

	void			Update			( float dt )			override;
	void			Render			( void )				override;
	void			HandleCollision	( const IBase* pOther )	override;
	void			HandleEvent(const SGD::Event* pEvent);


	float			GetDamage		( void )	const	{ return m_fDamage; }
	void			SetDamage		( float d )			{ m_fDamage	= d; }

};

