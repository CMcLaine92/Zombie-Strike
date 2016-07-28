#include "FastZombie.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "GameplayState.h"
#include "BehaviorManager.h"
#include "BaseBehavior.h"
#include "AnimationManager.h"
#include "Bullet.h"
#include "DestroyObjectMessage.h"

FastZombie::FastZombie()
{
	health = 100.0f;
	damage = 10.0f;
	//damage = 2.0f;
}


FastZombie::~FastZombie()
{
	
}



/*virtual*/ void FastZombie::HandleEvent(const SGD::Event* pEvent)
{

}

