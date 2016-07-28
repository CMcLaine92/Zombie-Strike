/***************************************************************
|	File:		AnimationManager.h
|	Author:		Jason Bloomfield
|	Course:		SGP1
|	Purpose:	AnimationManager class stores & maintains all game animations
***************************************************************/

#pragma once

#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_Color.h"
#include <string>
#include <map>

class Animation;
struct AnimTimeStamp;
class BaseObject;

class AnimationManager
{
public:

	/**********************************************************/
	// Singleton Accessor
	static AnimationManager* GetInstance(void);


	/**********************************************************/
	// Interface:
	bool	Load(std::string		xmlFilePath, std::string name);
	void	Update(AnimTimeStamp&	ats, float dt, BaseObject* destination = nullptr, void* data = nullptr);
	void	Render(AnimTimeStamp&	ats, SGD::Point position, float rotation = 0.0f, SGD::Color color = {255,255,255,255}, SGD::Size scale = { 1.0f, 1.0f });
	void	Shutdown(void);
	Animation* GetAnimation(std::string animName);

private:
	/**********************************************************/
	// SINGLETON!
	AnimationManager(void) = default;
	~AnimationManager(void) = default;

	AnimationManager(const AnimationManager&) = delete;
	AnimationManager& operator= (const AnimationManager&) = delete;


	/**********************************************************/
	// Data members
	std::map<std::string, Animation*>	m_mapAnimations;
};

