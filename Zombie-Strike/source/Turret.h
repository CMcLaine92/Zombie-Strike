#pragma once
#include "MovingObject.h"
#include "Weapon.h"
#include "../SGD Wrappers/SGD_Listener.h"

class BaseBehavior;
class Zombie;
//class Weapon;
class Player;

class Turret : public MovingObject, public Weapon, public SGD::Listener
{
public:
	Turret();
	~Turret();

	virtual void	Update				(float dt)							override;
	virtual void	Render				(void)								override;
	virtual void	HandleEvent			(const SGD::Event* pEvent);
	virtual void	HandleCollision		(const IBase* pOther)				override;

	virtual void	Fire				(float dt)								override;
	virtual int		GetType				(void)						const	override	{ return ObjectType::OBJ_TURRET; }
	void			SetShutDownEvent	(const char* pEvent)							{ ShutDownEvent = pEvent; }
	void			RetrieveBehavior	(std::string name);

	Zombie*			GetTarget			( void ) const	{ return m_pTarget; }
	void			SetTarget			( Zombie * ptr );

	//void			SetWeapon			( Weapon * ptr )	{ bulletmaker = ptr; }

	//Player*			GetOwner			( void ) const { return m_pOwner; }
	//void			SetOwner			( MovingObject* owner );



private:

	BaseBehavior*	currBehavior	= nullptr;
	SGD::HAudio*	fireSound		= nullptr;
	bool			isActive		= true;
	std::string		ShutDownEvent;
	Zombie*			m_pTarget		= nullptr;
	//Weapon*			bulletmaker		= nullptr;
	Player*			m_pOwner		= nullptr;



	friend class BaseBehavior;
};

