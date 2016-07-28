#include "BaseObject.h"
#include "AnimationManager.h"
#include "Animation.h"
#include "Frame.h"
#include "Player.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <cassert>
#include "GameplayState.h"
#include "HTPGameState.h"



BaseObject::~BaseObject()
{
	assert(m_unRefCount == 0 && "~Base - object was destroyed while references remain!");
}

/*virtual*/ SGD::Rectangle BaseObject::GetRect(void) const
{
	SGD::Rectangle collisionRect = AnimationManager::GetInstance()->GetAnimation(animation.m_strCurrAnimation)->GetFrames()[animation.m_nCurrFrame]->GetCollisionRect();

	SGD::Point renderPos;

	if (Game::GetInstance()->GetCurrState() == GameplayState::GetInstance())
	{
		renderPos = SGD::Point(m_ptPosition.x
			- GameplayState::GetInstance()->GetCamera()->GetPosition().x,
			m_ptPosition.y
			- GameplayState::GetInstance()->GetCamera()->GetPosition().y);
	}
	else
	{
		renderPos = SGD::Point(m_ptPosition.x
			- HTPGameState::GetInstance()->GetCamera()->GetPosition().x,
			m_ptPosition.y
			- HTPGameState::GetInstance()->GetCamera()->GetPosition().y);
	}

	SGD::Rectangle rect = SGD::Rectangle(renderPos - SGD::Size(collisionRect.right - collisionRect.left, collisionRect.bottom - collisionRect.top) *0.5f, SGD::Size(collisionRect.right - collisionRect.left, collisionRect.bottom - collisionRect.top));
	return rect;
	

	//return SGD::Rectangle(renderPos - m_szSize / 2, m_szSize);
	
}
/*virtual*/ void BaseObject::Render(void) /*override*/
{
	AnimationManager::GetInstance()->Render(animation, this->m_ptPosition, this->m_fRotation, { alpha, 255, 255, 255 }, m_szScale);
	//SGD::Point renderPos = SGD::Point(m_ptPosition.x - GameplayState::GetInstance()->GetCamera()->GetPosition().x, m_ptPosition.y - GameplayState::GetInstance()->GetCamera()->GetPosition().y);

	//SGD::Rectangle collisionRect = AnimationManager::GetInstance()->GetAnimation(animation.m_strCurrAnimation)->GetFrames()[animation.m_nCurrFrame]->GetCollisionRect();
	//
	//SGD::Rectangle rect = SGD::Rectangle(renderPos - m_szSize / 2, m_szSize);
	////rect.Offset(GameplayState::GetInstance()->GetCamera()->GetPosition().x, GameplayState::GetInstance()->GetCamera()->GetPosition().y);
	//SGD::GraphicsManager::GetInstance()->DrawRectangle(GetRect() , SGD::Color(0, 0, 0, 0), SGD::Color(255, 0, 0, 0));

}
void BaseObject::Update(float dt)
{
	AnimationManager::GetInstance()->Update(animation, dt);
}

/*virtual*/ void BaseObject::HandleCollision(const IBase* pOther)
{
	/* DO NOTHING */
	(void)pOther;		// unused parameter
}

/*virtual*/ void BaseObject::AddRef(void)
{
	assert(m_unRefCount != 0xFFFFFFFF && "BaseObject::AddRef - maximum reference count has been exceeded");

	++m_unRefCount;
}

/*virtual*/ void BaseObject::Release(void)
{
	--m_unRefCount;

	if (m_unRefCount == 0)
		delete this;
}


void BaseObject::SetAnimation(std::string animName)
{
	animation.m_strCurrAnimation = animName;
	animation.m_fCurrDuration = 0.0f;
	animation.m_nCurrFrame = 0;
}