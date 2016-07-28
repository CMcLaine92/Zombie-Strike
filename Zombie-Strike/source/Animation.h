/***************************************************************
|	File:		Animation.h
|	Author:		Jason Bloomfield
|	Course:		SGP1
|	Purpose:	Animation class stores data for a single animation
***************************************************************/

#pragma once

#include "../SGD Wrappers/SGD_Handle.h"
#include <vector>

class Frame;


class Animation
{
public:
	Animation();
	~Animation();


	/**********************************************************/
	// Accessors:
	SGD::HTexture		GetImage(void)	const			{ return m_hImage; }
	std::vector<Frame*>	GetFrames(void)	const			{ return m_vFrames; }
	bool				GetLooping(void)	const			{ return m_bIsLooping; }


	/**********************************************************/
	// Mutators:
	void				SetImage(SGD::HTexture	image)	{ m_hImage = image; }
	void				SetLooping(bool			loop)	{ m_bIsLooping = loop; }


	/**********************************************************/
	// Other Methods:
	void				AddFrame(Frame* frame)		{ m_vFrames.push_back(frame); }
	void				RemoveFrame(Frame* frame);
	void				RemoveAllFrames(void);



private:
	/**********************************************************/
	// data members:

	SGD::HTexture			m_hImage = SGD::INVALID_HANDLE;
	std::vector<Frame*>		m_vFrames;
	bool					m_bIsLooping = false;

};

