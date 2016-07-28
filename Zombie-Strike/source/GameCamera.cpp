#include "GameCamera.h"
#include "BaseObject.h"


void GameCamera::SetTarget(BaseObject* newTarget)
{
	if (target != nullptr)
	{
		target->Release();
		target = nullptr;
	}
	target = newTarget;
}

SGD::Rectangle GameCamera::GetRect(void) const
{
	return SGD::Rectangle(m_ptPostion, m_szSize);
}
