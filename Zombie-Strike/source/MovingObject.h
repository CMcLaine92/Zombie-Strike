#pragma once
#include "BaseObject.h"
#include "../SGD Wrappers/SGD_Geometry.h"	
#include <string>
#include <vector>
#include "Timer.h"
#include "Graph.h"


class MovingObject : public BaseObject
{
protected:

	SGD::Vector direction = { 0, -1 };
	SGD::Vector m_vtVelocity = { 0, 0 };
	float m_fMoveSpeed = 0.0f;
	Timer m_tShotTimer;
	Timer m_tWait;

	friend class FOV;


public:
	MovingObject() = default;
	~MovingObject() = default;


	virtual void			Update			(float elapsedTime)	 override;
	//virtual void			Render			(void)				 override;
	virtual void			Attack			(void)							{};
	virtual void			HandleCollision	(const IBase* pOther) override;


	//Accessors
	virtual int				GetType				(void) const override	{ return OBJ_MOVING; }
	SGD::Vector				GetVelocity			(void) const			{ return m_vtVelocity; }
	SGD::Vector				GetDirection		(void) const			{ return direction; }
	float					GetMoveSpeed		(void) const			{ return m_fMoveSpeed; }
	bool					UpdateAttackTime	(float dt)				{ return m_tShotTimer.Update(dt); }
	bool					UpdateWaitTime		(float dt)				{ return m_tWait.Update(dt); }


	//Mutators
	void					SetVelocity		(SGD::Vector newVeloctiy)	{ m_vtVelocity = newVeloctiy; }
	void					SetDirection	(SGD::Vector newDirection)	{ direction = newDirection; }
	void					SetMoveSpeed	(float newSpeed)			{ m_fMoveSpeed = newSpeed; }
	void					AddToShotTimer	(float newTime)				{ m_tShotTimer.AddTime(newTime); }
	void					AddToWaitTimer	(float newTime)				{ m_tWait.AddTime(newTime); }


};