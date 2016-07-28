#include "Grenade.h"
#include "DestroyObjectMessage.h"

Grenade::Grenade()
{
}


Grenade::~Grenade()
{
}

void Grenade::Update(float dt)
{
	speed -= 600.0f * dt;
	m_vtVelocity = direction * speed;
	MovingObject::Update(dt);
	if (speed > 375.0f)
		m_szScale += SGD::Size(1.0f, 1.0f) * dt;
	else
		m_szScale -= SGD::Size(1.0f, 1.0f) * dt;

	
	if (speed < 0)
	{
		speed = 0;
		SetAnimation("explosion");

	}
	if ((animation.m_strCurrAnimation == "explosion" && animation.m_nCurrFrame == 7) || IsDead())
	{
		DestroyObjectMessage* pMsg = new DestroyObjectMessage{ this };
		pMsg->QueueMessage();
		pMsg = nullptr;
	}
	

}
