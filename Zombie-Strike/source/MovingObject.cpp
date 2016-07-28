#include "MovingObject.h"
#include "BaseBehavior.h"
#include "BehaviorManager.h"
#include "AnimationManager.h"
#include "Game.h"


/*virtual*/ void MovingObject::Update(float dt)	 /*override*/
{
	m_ptPosition += m_vtVelocity * dt;
	BaseObject::Update(dt);
}

/*virtual*/ void MovingObject::HandleCollision(const IBase* pOther) /*override*/
{
	m_ptPosition -= m_vtVelocity * Game::GetInstance()->DeltaTime();
	m_vtVelocity = { 0, 0 };
}
