#pragma once
#include "MovingObject.h"
#include "../SGD Wrappers/SGD_Listener.h"
class Event;
class BaseBehavior;

class Zombie : public MovingObject, public SGD::Listener
{
public:
	Zombie();
	virtual ~Zombie();

	virtual void Update(float);

	virtual int GetType(void) const override { return OBJ_SLOW_ZOMBIE; }
	virtual void HandleEvent(const SGD::Event* pEvent) override;
	virtual void HandleCollision(const IBase* pOther) override;


	float GetHealth(void) const { return health; }
	float GetDamage(void) const { return damage; }
	bool IsAlive(void) const { return isAlive; }

	void SetHealth(float _health) { health = _health; }
	void SetDamage(float _damage) { damage = _damage; }
	void SetTarget(BaseObject* target);
	void RetrieveBehavior(std::string name);

protected:

	BaseObject* m_pTarget = nullptr;
	BaseBehavior* currBehavior = nullptr;
	float health = 100.0f;
	float damage = 10.0f;
	bool isAlive = true;


	friend class BaseBehavior;

};

