#pragma once

#include "../SGD Wrappers/SGD_Geometry.h"

class BaseObject;
class BaseBehavior;



class GameCamera
{
public:
	GameCamera()= default;
	~GameCamera() = default;

	SGD::Point GetPosition(void) const { return m_ptPostion; }
	void SetPostion(SGD::Point newPos) { m_ptPostion = newPos; }
	SGD::Size GetSize(void) const { return m_szSize; }
	void SetSize(SGD::Size newSize) { m_szSize = newSize; }
	void SetTarget(BaseObject* newTarget);
	BaseObject* GetTarget(void) const { return target; }

	SGD::Rectangle GetRect(void) const;

	

private: 

	SGD::Point m_ptPostion = { 0, 0 };
	SGD::Size m_szSize = { 0, 0 };
	BaseObject* target = nullptr;
	BaseBehavior* currBehavior = nullptr;
	
};

