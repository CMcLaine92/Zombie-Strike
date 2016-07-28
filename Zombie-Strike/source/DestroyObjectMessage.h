

#pragma once

#include "../SGD Wrappers/SGD_Message.h"	


class BaseObject;


class DestroyObjectMessage : public SGD::Message
{
public:
	DestroyObjectMessage(BaseObject* ptr);
	virtual ~DestroyObjectMessage();

	BaseObject*		GetEntity(void) const		{ return m_pObject; }

private:
	
	BaseObject*		m_pObject;

};

