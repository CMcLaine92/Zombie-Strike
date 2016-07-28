#include "BehaviorManager.h"
#include "BaseBehavior.h"

#include "AlertBehavior.h"
#include "PatrolBehavior.h"
#include "PlayerController.h"
#include "RotateTowardsBehavior.h"
#include "RunToBehavior.h"
#include "WaitBehavior.h"




/*static*/ BehaviorManager* BehaviorManager::GetInstance(void)
{
	static BehaviorManager s_Instance;	// stored in global memory once
	return &s_Instance;
}



/*virtual*/	bool BehaviorManager::Initialize(void)
{
	BaseBehavior* alertBehavior = new AlertBehavior();
	ManagerBehaviors.insert(std::pair<std::string, BaseBehavior*>("hostile", alertBehavior));
	
	BaseBehavior* patrolBehavior = new PatrolBehavior();
	ManagerBehaviors.insert(std::pair<std::string, BaseBehavior*>("move", patrolBehavior));

	BaseBehavior* rotateBehavior = new RotateTowardsBehavior();
	ManagerBehaviors.insert(std::pair<std::string, BaseBehavior*>("rotate", rotateBehavior));

	BaseBehavior* runToBehavior = new RunToBehavior();
	ManagerBehaviors.insert(std::pair<std::string, BaseBehavior*>("runTo", runToBehavior));

	BaseBehavior* waitBehavior = new WaitBehavior();
	ManagerBehaviors.insert(std::pair<std::string, BaseBehavior*>("wait", waitBehavior));
	
	BaseBehavior* playerController = new PlayerController();
	ManagerBehaviors.insert(std::pair<std::string, BaseBehavior*>("playerController", playerController));



	return true;
}
/*virtual*/	bool BehaviorManager::Terminate(void)
{
	std::map<std::string, BaseBehavior*>::iterator iter = ManagerBehaviors.begin();
	for (; iter != ManagerBehaviors.end(); iter++)
	{
		delete iter->second;
	}
	ManagerBehaviors.clear();

	return true;
}


