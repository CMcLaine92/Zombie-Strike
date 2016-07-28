/***************************************************************
|	File:		Frame.h
|	Author:		Jason Bloomfield
|	Course:		SGP1
|	Purpose:	Frame class stores animation data for a single frame
***************************************************************/

#pragma once

#include "../SGD Wrappers/SGD_Geometry.h"
#include <string>

class Frame
{
public:
	Frame() = default;
	~Frame() = default;


	/**********************************************************/
	// Accessors:
	SGD::Rectangle		GetSourceRect(void)	const	{ return m_rctSourceRect; }
	SGD::Rectangle		GetCollisionRect(void)	const	{ return m_rctCollisionRect; }
	SGD::Point			GetAnchorPoint(void)	const	{ return m_ptAnchorPoint; }
	SGD::Point			GetRotationPoint(void)	const	{ return m_ptRotationPoint; }
	float				GetDuration(void)	const	{ return m_fDuration; }
	std::string			GetTrigger(void)	const	{ return m_sTrigger; }


	/**********************************************************/
	// Mutators:
	void				SetSourceRect(SGD::Rectangle	src)	{ m_rctSourceRect = src; }
	void				SetCollisionRect(SGD::Rectangle	col)	{ m_rctCollisionRect = col; }
	void				SetAnchorPoint(SGD::Point		ap)	{ m_ptAnchorPoint = ap; }
	void				SetRotationPoint(SGD::Point		rp)	{ m_ptRotationPoint = rp; }
	void				SetDuration(float				dur)	{ m_fDuration = dur; }
	void				SetTrigger(std::string		trig)	{ m_sTrigger = trig; }


private:

	SGD::Rectangle	m_rctSourceRect = SGD::Rectangle{ 0, 0, 0, 0 };
	SGD::Rectangle	m_rctCollisionRect = SGD::Rectangle{ 0, 0, 0, 0 };

	SGD::Point		m_ptAnchorPoint = SGD::Point{ 0, 0 };
	SGD::Point		m_ptRotationPoint = SGD::Point{ 0, 0 };

	float			m_fDuration = 0.0f;
	std::string		m_sTrigger = "";





};
