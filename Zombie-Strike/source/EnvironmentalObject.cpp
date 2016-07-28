#include "EnvironmentalObject.h"
#include "GameplayState.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "HTPGameState.h"



EnvironmentalObject::EnvironmentalObject() : Listener(this)
{

}
EnvironmentalObject::~EnvironmentalObject()
{
	//UnregisterFromEvent(event.c_str());
}

void EnvironmentalObject::HandleCollision(const IBase* pOther)
{
}



/*virtual*/ SGD::Rectangle EnvironmentalObject::GetRect(void) const
{
	SGD::Point renderPos;
	
	if (HTPGameState::GetInstance()->GetIsCurrState() == true)
		renderPos = SGD::Point(m_ptPosition.x - HTPGameState::GetInstance()->GetCamera()->GetPosition().x,
		m_ptPosition.y - HTPGameState::GetInstance()->GetCamera()->GetPosition().y);
	else
		renderPos = SGD::Point(m_ptPosition.x - GameplayState::GetInstance()->GetCamera()->GetPosition().x,
		m_ptPosition.y - GameplayState::GetInstance()->GetCamera()->GetPosition().y);


	return SGD::Rectangle({ renderPos, m_szSize });
}
