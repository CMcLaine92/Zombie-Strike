/***************************************************************
|	File:		AnimTimeStamp.h
|	Author:		Jason Bloomfield
|	Course:		SGP1
|	Purpose:	AnimTimeStamp class stores data for a single animation
***************************************************************/

#pragma once

#include <string>

struct AnimTimeStamp
{

	std::string		m_strCurrAnimation = "";
	int				m_nCurrFrame = 0;
	float			m_fCurrDuration = 0.0f;


};
