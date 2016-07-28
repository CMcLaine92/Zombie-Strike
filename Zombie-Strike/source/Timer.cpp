#include "Timer.h"


bool Timer::Update(float dt)
{
if (m_fCurrTime > 0.0f)
	{
		m_fCurrTime -= dt;
		return false;

	}

	else 
	{
		if (maxTime > 0.0f)			//resets the currTime to the max time if it was set by the user,
			m_fCurrTime = maxTime;
		else if (m_fCurrTime < 0.0f)	//otherwise, caps at 0
			m_fCurrTime = 0.0f;
		return true;
	}

}