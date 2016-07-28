#include "BloodSplatter.h"
#include "DestroyObjectMessage.h"


BloodSplatter::BloodSplatter()
{
	activeTimer.AddTime(5.0f);
}


BloodSplatter::~BloodSplatter()
{
}

void BloodSplatter::Update(float dt)
{
	if (activeTimer.Update(dt))
		return;
	else
		alpha -= (unsigned char)(100.0f * dt);
		

	if (alpha <= 0)
	{
		DestroyObjectMessage* dMsg = new DestroyObjectMessage{ this };
		dMsg->QueueMessage();
		dMsg = nullptr;
	}
}
void BloodSplatter::HandleCollision(const IBase* pOther)
{

}
