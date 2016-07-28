#pragma once

#include "SandBag.h"

class House : public SandBag
{
public:
	House();
	virtual ~House();

	void			Update			( float dt )			override;
	void			Render			( void )				override;
	void			HandleCollision	( const IBase* pOther )	override;
	void			HandleEvent(const SGD::Event* pEvent)	override;


};

