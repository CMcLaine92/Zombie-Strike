#include "CreateBloodMsg.h"
#include "MessageID.h"

CreateBloodMsg::CreateBloodMsg(SGD::Point pos) : Message(MessageID::MSG_CREATE_BLOOD)
{
	spawnPos = pos;
}


CreateBloodMsg::~CreateBloodMsg()
{
}
