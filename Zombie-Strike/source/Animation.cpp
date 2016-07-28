/***************************************************************
|	File:		Animation.cpp
|	Author:		Jason Bloomfield
|	Course:		SGP1
|	Purpose:	Animation class stores data for a single animation
***************************************************************/

#include "Animation.h"
#include "Frame.h"

#include "../SGD Wrappers/SGD_GraphicsManager.h"


Animation::Animation()
{
}
Animation::~Animation()
{
	// Unload texture
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hImage);

	// Destroy all frames
	RemoveAllFrames();
}


/**********************************************************/
// RemoveFrame
void Animation::RemoveFrame( Frame* frame )
{
	for (unsigned int i = 0; i < m_vFrames.size(); ++i)
	{
		if (m_vFrames[i] == frame)
		{
			delete m_vFrames[i];
			m_vFrames.erase(m_vFrames.begin() + i--);
			break;
		}
	}
}


/**********************************************************/
// RemoveAllFrames
void Animation::RemoveAllFrames(void)
{
	for (unsigned int i = 0; i < m_vFrames.size(); ++i)
		delete m_vFrames[i];
	m_vFrames.clear();
}

