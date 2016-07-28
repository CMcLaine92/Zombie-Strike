/***************************************************************
|	File:		AnimationManager.h
|	Author:		Jason Bloomfield
|	Course:		SGP1
|	Purpose:	AnimationManager class stores & maintains all game animations
***************************************************************/

#include "AnimationManager.h"
#include "tinyxml.h"

#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_Handle.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "Animation.h"
#include "AnimTimeStamp.h"
#include "Frame.h"
#include "GameplayState.h"
#include "BaseObject.h"
#include "Game.h"
#include "HTPGameState.h"


/**************************************************************/
// GetInstance
/*static*/ AnimationManager* AnimationManager::GetInstance(void)
{
	static AnimationManager s_Instance;

	return &s_Instance;
}


/**************************************************************/
// Load
bool AnimationManager::Load(std::string xmlFilePath, std::string name)
{
	// Create the TinyXML Document
	TiXmlDocument doc;


	// Attempt to load from XML
	if (doc.LoadFile(xmlFilePath.c_str()) == false)
		return false;


	// Access the root element from the document
	TiXmlElement* pRoot = doc.RootElement();
	if (pRoot == nullptr)
		return false;


	// Access the first Animation element "Animation" of the root
	TiXmlElement* pAnimation = pRoot->FirstChildElement("Animation");


	// Iterate through the list of children
	while (pAnimation != nullptr)
	{
		// Create a new Animation to store the date
		Animation * animation = new Animation();
		bool looping;
		char spritesheetPath[90];
		SGD::HTexture image;


		// Read the animation's Attribute "looping"
		int loop;
		pAnimation->Attribute("looping", &loop);

		// Set the looping bool
		looping = loop == 0 ? false : true;
		/*
		if (loop == 0)
		looping = false;
		else
		looping = true;
		*/
		animation->SetLooping(looping);


		// Read the animation's sprite sheet name
		const char* pText = pAnimation->GetText();
		if (pText != nullptr)
			strcpy_s(spritesheetPath, _countof(spritesheetPath), pText);

		// Load the image from the file path
		char path[90] = "resource/graphics/";
		strcat_s(path, _countof(path), spritesheetPath);
		image = SGD::GraphicsManager::GetInstance()->LoadTexture(path);
	
		animation->SetImage(image);


		// Add the animation info to the map
		m_mapAnimations[name] = animation;



		// Access the first Frame element "Frame" of the Animation root
		TiXmlElement* pFrame = pAnimation->FirstChildElement("Frame");
		while (pFrame != nullptr)
		{
			// Create a new Frame to store the date
			Frame * frame = new Frame;
			double sx, sy, sw, sh;
			double cx, cy, cw, ch;
			double px, py;
			double rx, ry;
			double dur;
			char trigger[25];


			// Read the frame's Attributes "x", "y", & "duration"
			pFrame->Attribute("sx", &sx);
			pFrame->Attribute("sy", &sy);
			pFrame->Attribute("sw", &sw);
			pFrame->Attribute("sh", &sh);
			pFrame->Attribute("cx", &cx);
			pFrame->Attribute("cy", &cy);
			pFrame->Attribute("cw", &cw);
			pFrame->Attribute("ch", &ch);
			pFrame->Attribute("px", &px);
			pFrame->Attribute("py", &py);
			pFrame->Attribute("rx", &rx);
			pFrame->Attribute("ry", &ry);
			pFrame->Attribute("duration", &dur);


			// Read the frame's trigger string
			const char* pTrigText = pFrame->GetText();
			if (pTrigText != nullptr)
				strcpy_s(trigger, 25, pTrigText);


			// Set the frame's data members
			//SGD::Point	sourcepoint	= SGD::Point{ static_cast<float>(sx), static_cast<float>(sy) };
			//SGD::Size	sourcesize	= SGD::Size{ static_cast<float>(sw), static_cast<float>(sh) };
			//SGD::Point	colliderpoint	= SGD::Point{ static_cast<float>(cx), static_cast<float>(cy) };
			//SGD::Size	collidersize	= SGD::Size{ static_cast<float>(cw), static_cast<float>(ch) };
			//SGD::Rectangle	fsource = SGD::Rectangle{ sourcepoint, sourcesize };
			//SGD::Rectangle	fcollider = SGD::Rectangle{ colliderpoint, collidersize };
			SGD::Rectangle	fsource = SGD::Rectangle{ static_cast<float>(sx), static_cast<float>(sy), static_cast<float>(sw), static_cast<float>(sh) };
			SGD::Rectangle	fcollider = SGD::Rectangle{ static_cast<float>(cx), static_cast<float>(cy), static_cast<float>(cw), static_cast<float>(ch) };
			SGD::Point		ap = { static_cast<float>(px), static_cast<float>(py) };
			SGD::Point		rp = { static_cast<float>(rx), static_cast<float>(ry) };

			frame->SetSourceRect(fsource);
			frame->SetCollisionRect(fcollider);
			frame->SetAnchorPoint(ap);
			frame->SetRotationPoint(rp);
			frame->SetDuration(static_cast<float>(dur));
			frame->SetTrigger(trigger);


			// Add the frame to the animation
			m_mapAnimations[name]->AddFrame(frame);

			// Iterate to the next animation element "Animation"
			pFrame = pFrame->NextSiblingElement("Frame");
		}



		// Iterate to the next animation element "Animation"
		pAnimation = pAnimation->NextSiblingElement("Animation");
	}



	return true;
}


/**************************************************************/
// Update
void AnimationManager::Update(AnimTimeStamp& ats, float dt, BaseObject* destination, void* data)
{
	// Was an animation to use NOT set? 
	if (ats.m_strCurrAnimation == "")
		return;


	// Is the animation NOT in the AnimationManager? 
	auto findresult = m_mapAnimations.find(ats.m_strCurrAnimation);
	if (findresult == m_mapAnimations.end())
		return;


	// Get the selected animation, & it's current frame
	Animation* pCurrAnimation = m_mapAnimations[ats.m_strCurrAnimation];
	Frame* pCurrFrame = pCurrAnimation->GetFrames()[ats.m_nCurrFrame];


	// Ready to go to next frame of animation?
	if (ats.m_fCurrDuration < pCurrFrame->GetDuration())
	{
		// No: update current frame timer
		ats.m_fCurrDuration += dt;
	}
	else if (ats.m_fCurrDuration >= pCurrFrame->GetDuration())
	{
		// Did this frame trigger an event?
		if (pCurrFrame->GetTrigger() != "NONE")
		{
			// Queue event from Frame Trigger
			SGD::Event* pEvent = new SGD::Event{ pCurrFrame->GetTrigger().c_str(), data, this };
			pEvent->QueueEvent(destination);
			pEvent = nullptr;

			// Send event immediately from Frame Trigger
			
			/*SGD::Event event = { pCurrFrame->GetTrigger().c_str(), data, this };
			event.SendEventNow(destination);
			*/

			if (destination != nullptr)
			{
				destination->Release();
				destination = nullptr;
			}
		}


		// Yes: move to next frame of animation
		ats.m_nCurrFrame++;
		ats.m_fCurrDuration = 0.0f;


		// Has it reached the end?
		if (ats.m_nCurrFrame == pCurrAnimation->GetFrames().size())
		{
			// Should the animation loop from the beginning?
			//	pCurrAnimation->GetLooping() == true ? ats.m_nCurrFrame = 0 : --ats.m_nCurrFrame;

			if (pCurrAnimation->GetLooping() == true)
			{
				// Yes: restart animation at 1st frame
				ats.m_nCurrFrame = 0;
			}
			else
			{
				// No: stop on the last valid frame
				--ats.m_nCurrFrame;
			}
		}
	}


}


/**************************************************************/
// Render
void AnimationManager::Render(AnimTimeStamp& ats, SGD::Point position, float rotation, SGD::Color color, SGD::Size scale)
{
	// Was the animation to use NOT set? 
	if (ats.m_strCurrAnimation == "")
		return;


	// Is the animation NOT in the AnimationManager? 
	auto findresult = m_mapAnimations.find(ats.m_strCurrAnimation);
	if (findresult == m_mapAnimations.end())
		return;


	// Get the selected animation, & it's current frame
	Animation* pCurrAnimation = m_mapAnimations[ats.m_strCurrAnimation];
	Frame* pCurrFrame = pCurrAnimation->GetFrames()[ats.m_nCurrFrame];


	// Get the anchor point for the current frame
	SGD::Point		anchor = pCurrFrame->GetAnchorPoint();
	SGD::Rectangle	source = pCurrFrame->GetSourceRect();

	SGD::Point renderPos;
	
	if (Game::GetInstance()->GetCurrState() == GameplayState::GetInstance())
	{
		renderPos = SGD::Point(position.x - anchor.x - GameplayState::GetInstance()->GetCamera()->GetPosition().x, position.y - anchor.y - GameplayState::GetInstance()->GetCamera()->GetPosition().y);
	}

	else
		renderPos = SGD::Point(position.x - anchor.x - HTPGameState::GetInstance()->GetCamera()->GetPosition().x, position.y - anchor.y - HTPGameState::GetInstance()->GetCamera()->GetPosition().y);
	
	// Offset the position by the frame's anchor-point to get to the top-left corner
	SGD::GraphicsManager::GetInstance()->DrawTextureSection(
		pCurrAnimation->GetImage(),
		renderPos,
		pCurrFrame->GetSourceRect(),
		rotation,
		{ pCurrFrame->GetRotationPoint().x, pCurrFrame->GetRotationPoint().y },
		color,
		scale);
	
}


/**************************************************************/
// Shutdown
void AnimationManager::Shutdown(void)
{
	std::map<std::string, Animation*>::iterator /*auto*/ iter = m_mapAnimations.begin();

	for (; iter != m_mapAnimations.end(); iter++)
	{
		//std::string animname = iter->first;
		delete iter->second;
	}

	m_mapAnimations.clear();
}


/**************************************************************/
// GetAnimation
 Animation* AnimationManager::GetAnimation(std::string animName) 
{
	 return m_mapAnimations[animName];
}
