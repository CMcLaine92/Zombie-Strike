#pragma once

#include "EnvironmentalObject.h"

class SandBag : public EnvironmentalObject
{
protected:

	float	m_fCurrHP;
	float	m_fMaxHP;


public:
	SandBag();
	virtual ~SandBag();

	void			Update			( float dt )			override;
	void			Render			( void )				override;
	void			HandleCollision	( const IBase* pOther )	override;
	void			HandleEvent(const SGD::Event* pEvent);


	float			GetCurrHP		( void )	const	{ return m_fCurrHP; }
	float			GetMaxHP		( void )	const	{ return m_fMaxHP; }

	void			SetCurrHP		( float hp )		{ m_fCurrHP	= hp; }
	void			SetMaxHP		( float hp )		{ m_fMaxHP	= hp; }

	SGD::Rectangle GetRect(void) const { return BaseObject::GetRect(); }

};

