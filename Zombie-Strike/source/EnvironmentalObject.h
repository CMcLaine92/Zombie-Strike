#pragma once
#include "BaseObject.h"
#include "../SGD Wrappers/SGD_Listener.h"
class EnvironmentalObject : public BaseObject, public SGD::Listener
{
protected:

	int type = OBJ_BASE;
	
	bool isActive = true;

public:
	EnvironmentalObject();
	virtual ~EnvironmentalObject();
	//virtual void Render(void) {}
//	virtual SGD::Rectangle GetRect(void) const;
	virtual int GetType(void) const { return type; }
	virtual void HandleCollision(const IBase* pOther) override;


	bool IsActive(void) const { return isActive; }

	void SetActive(bool state) { isActive = state; }

	void SetType(int newType) { type = newType; }

	SGD::Rectangle GetRect(void) const;

};

