#pragma once
#include "../SGD Wrappers/SGD_Geometry.h"	

class IBase
{
protected:
	IBase() = default;
	virtual ~IBase() = default;

public:
	
	virtual void	Update(float elapsedTime) = 0;
	virtual void	Render(void) = 0;

	virtual int		GetType(void)	const = 0;
	virtual SGD::Rectangle GetRect(void)	const = 0;
	virtual void	HandleCollision(const IBase* pOther) = 0;


	virtual void	AddRef(void) = 0;
	virtual void	Release(void) = 0;
};

