#pragma once
#include <map>

class BaseBehavior;


class BehaviorManager
{

public:

	static BehaviorManager* GetInstance(void);

	bool		Initialize(void);
	bool		Terminate(void);

	std::map<std::string, BaseBehavior*>& GetBehaviors() { return ManagerBehaviors; }

private:

	BehaviorManager(void) = default;
	~BehaviorManager(void) = default;

	BehaviorManager(const BehaviorManager&) = delete;
	BehaviorManager&	operator=	(const BehaviorManager&) = delete;


	//Data Memebers
	std::map<std::string, BaseBehavior*> ManagerBehaviors;

};

