#pragma once
#include "IBase.h"
#include "../SGD Wrappers/SGD_Declarations.h"	
#include "AnimTimeStamp.h"

class BaseObject : public IBase
{
protected:
	SGD::Point m_ptPosition = { 0, 0 };
	SGD::Size m_szSize = { 0, 0 };
	float m_fRotation = 0.0f;
	SGD::Size m_szScale = { 1.0f, 1.0f };
	AnimTimeStamp animation;
	unsigned char alpha = (char)255;


private:
	unsigned int m_unRefCount = 1;


public:
	enum ObjectType{ OBJ_BASE, OBJ_MOVING, OBJ_PLAYER, OBJ_SLOW_ZOMBIE, OBJ_FAST_ZOMBIE, OBJ_FAT_ZOMBIE, OBJ_EXPLODING_ZOMBIE, OBJ_TANK_ZOMBIE, OBJ_TURRET, 
		OBJ_SANDBAG, OBJ_LANDMINE, OBJ_BARBEDWIRE, OBJ_BULLET, OBJ_SPAWNER, OBJ_VOMIT,
		 OBJ_WALL, OBJ_DOOR, OBJ_TRIGGER, OBJ_IGNORE, OBJ_PLAYERCOLLISION };

	BaseObject() = default;
	~BaseObject();
	


	virtual void			Update			(float elapsedTime)	 override;
	virtual void			Render			(void)				 override;

	virtual int				GetType			(void)	const { return ObjectType::OBJ_BASE; }
	virtual SGD::Rectangle	GetRect			(void)	const;
	virtual void			HandleCollision	(const IBase* pOther) override;

	virtual void			AddRef			(void) final; 
	virtual void			Release			(void) final;


	//Accessors
	SGD::Point		GetPosition			(void) const	{ return m_ptPosition; }
	SGD::Size		GetSize				(void) const	{ return m_szSize; }
	float			GetRotation			(void) const	{ return m_fRotation; }
	SGD::Size			GetScale(void) const	{ return m_szScale; }
	std::string		GetAnimation		(void) const	{ return animation.m_strCurrAnimation; }
	AnimTimeStamp	GetAnimationStamp	(void) const	{ return animation; }


	//Mutators
	void			SetPosition			(SGD::Point	pos)		{ m_ptPosition = pos; }
	void			SetSize				(SGD::Size size)		{ m_szSize = size; }
	void			SetRotation			(float rad)				{ m_fRotation = rad; }
	void			SetAnimation		(std::string animName);
	void SetScale(SGD::Size scale) { m_szScale = scale; }
};

