#include "PickUp.h"
#include "DestroyObjectMessage.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "Player.h"

PickUp::PickUp()
{
}

PickUp::~PickUp()
{
}

/*virtual*/ void PickUp::HandleCollision(const IBase* pOther) /*override*/
{
	if (pOther->GetType() == OBJ_PLAYER)
	{
	/*	switch (m_nType)
		{
			case ObjectType::OBJ_POWERCORE:
				{
					SGD::Event*msg = new SGD::Event{ "PICK_UP_CORE" };
					msg->QueueEvent((Player*)pOther);
					msg = nullptr;
				}
				break;

			case ObjectType::OBJ_STIMPACK:
				{
					SGD::Event*msg = new SGD::Event{ "PICK_UP_STIM" };
					msg->QueueEvent((Player*)pOther);
					msg = nullptr;
				}
				break;
			default:
				break;
		}*/


		DestroyObjectMessage* dMsg = new DestroyObjectMessage{ this };
		dMsg->QueueMessage();
		dMsg = nullptr;
	}

}

///*virtual*/ SGD::Rectangle	PickUp::GetRect(void)	const
//{
//	return SGD::Rectangle();
//}

