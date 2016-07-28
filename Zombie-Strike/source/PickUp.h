#pragma once
#include "BaseObject.h"
class PickUp : public BaseObject
{

	int m_nType = OBJ_BASE;

public:
	
	PickUp();
	~PickUp();
	//virtual void Render() override;
	virtual void HandleCollision(const IBase* pOther) override;
	//virtual SGD::Rectangle	GetRect(void)	const;
	virtual int GetType(void) const override { return m_nType; }
	void SetType(int type) { m_nType = type; }
};

