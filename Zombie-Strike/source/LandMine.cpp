#include "LandMine.h"
#include "AnimationManager.h"
#include "Animation.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "GameplayState.h"
#include "../SGD Wrappers/SGD_Event.h"


LandMine::LandMine()
{
	this->SetType(ObjectType::OBJ_LANDMINE);
	this->SetAnimation("landmine");

	RegisterForEvent("REPAIR_LANDMINES");
}

LandMine::~LandMine()
{
	UnregisterFromEvent("REPAIR_LANDMINES");

}

void LandMine::Update( float dt )
{
	if (this->isActive == false)
		return;


	BaseObject::Update(dt);


	// on last frame of expolsion animation
	int numframes = AnimationManager::GetInstance()->GetAnimation("explosion")->GetFrames().size();
	numframes--;

	if (this->GetAnimation() == "explosion" && this->GetAnimationStamp().m_nCurrFrame == numframes)
	{
		// deactivate landmine
		this->isActive = false;
	}


}

void LandMine::Render( void )
{
	if (this->isActive == false)
		return;


	BaseObject::Render();
}

void LandMine::HandleCollision( const IBase* pOther )
{
	if (this->isActive == false)
		return;


	// zombie collision
	if (pOther->GetType() == ObjectType::OBJ_SLOW_ZOMBIE ||
		pOther->GetType() == ObjectType::OBJ_FAT_ZOMBIE || 
		pOther->GetType() == ObjectType::OBJ_FAST_ZOMBIE )
	{
		// activated mine
		if (this->GetAnimation() == "testLandmine" || this->GetAnimation() == "landmine")
		{
			// trigger explosion
			this->SetAnimation("explosion");
			SGD::AudioManager::GetInstance()->PlayAudio(Game::GetInstance()->explosion, false);
		}

		// exploding mine
		else if (this->GetAnimation() == "explosion")
		{
			// insta-kill zombies caught in explosion
		}
		//isActive = false;
	}

}

void LandMine::HandleEvent(const SGD::Event* pEvent)
{
	if (pEvent->GetEventID() == "REPAIR_LANDMINES")
	{
		isActive = true;
	}
}

SGD::Rectangle LandMine::GetRect() const
{

	return BaseObject::GetRect();
}
