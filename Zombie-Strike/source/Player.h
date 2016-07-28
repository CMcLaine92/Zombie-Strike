#pragma once

#include "MovingObject.h"
#include "../SGD Wrappers\SGD_Listener.h"
#include "AnimTimeStamp.h"
#include "Timer.h"
#include "HUD.h"
#include "../SGD Wrappers/SGD_Handle.h"
#include "GamerProfile.h"
#include "AnimTimeStamp.h"

class BaseBehavior;
class HAudio;
class HVoice;
class Weapon;


//struct GamerProfile
//{
//	float MaxEnergy = 0.0f;
//	float MaxStamina;
//	float CamoMultiplier;
//	float SpeedMultiplier;
//	float RadarMultiplier;
//	int LevelsComplete = 0;
//	std::string path;
//	bool m_bHasKey = false;
//	bool CheckPointReached;
//
//	
//};

struct Attributes
{
	float	m_fMovementSpeed	= 80.0f;
	float	m_fSpeedMultiplier	= 1.0f;
	float	m_fMaxEnergy		= 100.0f;
	float	m_fCurrEnergy		= 100.0f;
	float	m_fEnergyRegen		= 20.0f;
	float	m_fCurrStamina		= 100.0f;
	float	m_fMaxStamina		= 100.0f;
	float	m_fRadarMultiplier	= 1.0f;
	float	m_fCamoMultiplier	= 1.0f;
	float	m_fStaminaRegen		= 20.0f;
	float	m_fStunRange		= 0.0f;
	float	m_fCamoCost			= 10.0f;
	float	m_fRadarCost		= 50.0f;
	float	m_fSprintCost		= 20.0f;
};


class Player : public MovingObject
{
	GamerProfile	profile;
	Attributes		m_Attributes;

	//Weapon* pistol = nullptr;
	//Weapon* shotgun = nullptr;
	//Weapon* arifle = nullptr;
	//Weapon* sniper = nullptr;
	//Weapon* flameThrower = nullptr;




	unsigned int	m_unCurrAbility		= 0;
	bool			m_bIsSprinting		= false;
	bool			m_bMoving			= false;
	bool			m_bIsAlive			= true;
	bool			m_bIsCamoOn			= false;
	bool			m_bLevelCompleted	= false;

	BaseBehavior*	controller			= nullptr;
	HUD				hud;

	Timer			energyReboot;

	SGD::HAudio*	m_hDeath			= nullptr;
	SGD::HAudio*	m_hHurt				= nullptr;
	SGD::HVoice		voice;

	SGD::Point		m_rectAbilityPoint;
	SGD::Size		m_rectAbilitySize;

	int				m_nNumTurrets		= 3;

	float			m_fCurrHP			= 0.0f;
	float			m_fMaxHP			= 100.0f;
	bool			m_bIsPlacingTurret = false;

public:

	Player();
	~Player();


	virtual void		Update				(float dt)					override;
	virtual void		Render				(void)						override;
	virtual void		HandleEvent			(const SGD::Event* pEvent);
	virtual void		HandleCollision		(const IBase* pOther)		override;
	virtual void		Attack				(void)						override;
	virtual void		SpawnTurret			(void);


	// Accessors
	virtual int			GetType				(void) const override	{ return ObjectType::OBJ_PLAYER; }
	unsigned int		GetCurrAbility		(void) const			{ return m_unCurrAbility; }
	const Attributes*	GetAttributes		(void) const			{ return &m_Attributes; }
	SGD::HAudio*		GetDeathSFX			(void) const			{ return m_hDeath; }
	SGD::HVoice			GetVoice			(void) const			{ return voice; }
	GamerProfile&		GetProfile()		{ return profile; }

	// Mutators
	void				RetrieveBehavior	(std::string name);
	void				SetGamerProfile		(GamerProfile _profile)		{ profile = _profile; }
	void				SetAlpha			(unsigned char newAlpha)	{ alpha = newAlpha; }
	void				SetHealth(float newHealth)				{ m_fCurrHP = newHealth; }

	void				SetVoice			(SGD::HVoice v)				{ voice = v; }
	void				SetIsPlacingTurret(bool state)						{ m_bIsPlacingTurret = state; }

	bool isPlacingTurret(void) const { return m_bIsPlacingTurret; }
	// Other methods
	bool				IsMoving			(void) const				{ return m_bMoving; }
	bool				IsSprinting			(void) const				{ return m_bIsSprinting; }
	bool				isLevelCompleted	(void) const				{ return m_bLevelCompleted; }

	int					GetNumTurrets		(void) const				{ return m_nNumTurrets; }
	void				SetNumTurrets		(int tur)					{ m_nNumTurrets = tur; }

	void				AddOneTurret		(void)						{ profile.numTurrets++; }
	void				MinusOneTurrets(void)						{ profile.numTurrets--; }

	float				GetCurrHealth		(void) const				{ return m_fCurrHP; }
	float				GetMaxHealth		(void) const				{ return m_fMaxHP; }

	void				CheckDamage			(void);

	bool				GoodTurretPosition	(void) const;
	SGD::Point			GetTurretPosition	(void) const;




	friend class BaseBehavior;
	friend class PlayerController;
	friend class HUD;
};

