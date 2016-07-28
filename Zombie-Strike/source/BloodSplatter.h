#pragma once
#include "BaseObject.h"
#include "Timer.h"


class BloodSplatter : public BaseObject
{

public:
	BloodSplatter();
	virtual ~BloodSplatter();

	virtual void Update(float dt) override;
	virtual void HandleCollision(const IBase* pOther) override;
	Timer activeTimer;
	bool isActive = true;
};

