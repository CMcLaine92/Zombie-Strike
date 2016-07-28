/***************************************************************
|	File:		HighScoreState.cpp
|	Author:		Conner McLaine
|	Course:		SGD 1407
|	Purpose:	HighScoreState class loads, sorts, and displays
				high scores.
***************************************************************/

#include "HighScoreState.h"

#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"
#include "Game.h"
#include "BitmapFont.h"


#include <fstream>


/**************************************************************/
// GetInstance
//	- store the ONLY instance in global memory
//	- return the only instance by pointer
/*static*/ HighScoreState* HighScoreState::GetInstance(void)
{
	static HighScoreState s_Instance;

	return &s_Instance;
}


/**************************************************************/
// Enter
//	- reset the game & load resources
/*virtual*/ void HighScoreState::Enter(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	highscoreTimer.AddTime(5.0f);
	// Reset the cursor to the top
	// (commented out to keep the last cursor position)
	//m_nCursor = 0;
	

	
	std::wifstream fin;
	
	
	fin.open("resource/config/highscores.txt");

	if (fin.is_open())
	{
		
		for (unsigned int i = 0; i < 11; i++)
		{
			HighScore temp;
			
			fin >> temp.intials >> temp.waves;
			scores.push_back(temp); 
			fin.ignore(INT_MAX, '\n');
		}
	}

	




	SortByScore();
}

/**************************************************************/
// Exit
//	- deallocate / unload resources
/*virtual*/ void HighScoreState::Exit(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();



	std::wofstream fout; 
	fout.open("resource/config/highscores.txt");
	if (fout.is_open())
	{
		for (unsigned int i = 0; i < 10; i++)
			fout << scores[i].intials.c_str() << '\t' << scores[i].waves << '\n';
	}
	fout.close();

	scores.clear();

	
}


/**************************************************************/
// Input
//	- handle user input
/*virtual*/ bool HighScoreState::Input(void)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();




	// Select an option?
	if (pInput->IsKeyPressed(SGD::Key::Escape) == true || pInput->IsButtonPressed(0, 2) == true)
	{
		Game::GetInstance()->RemoveState();

	}
	

	return true;	// keep playing
}


/**************************************************************/
// Update
//	- update entities / animations
/*virtual*/ void HighScoreState::Update(float dt)
{
	if (highscoreTimer.Update(dt))
	{
		Game::GetInstance()->RemoveState();
	}
}


/**************************************************************/
// Render
//	- render entities / menu options
/*virtual*/ void HighScoreState::Render(void)
{
	// Use the game's font
	const BitmapFont* pFont = Game::GetInstance()->GetFont();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	// Align text based on window width
	float width = Game::GetInstance()->GetScreenWidth();
	float height = Game::GetInstance()->GetScreenHeight();
	pFont->Draw("High Scores", {width * 0.4f, height * 0.1f}, 1.0f, { 100, 150, 150 });


	//pGraphics->DrawTexture(background, { 0, 0 });
	unsigned int count = 1;
	float spacing = 100.0f;
	for (unsigned int i = 0; i < 10; i++)
	{
		
		SGD::OStringStream score;
		score << scores[i].intials.c_str() << "\t" << scores[i].waves;
		pFont->Draw(score.str().c_str(), { 200, spacing + ((32 * .75f) * count) }, .75f, { 100, 150, 150});
		spacing += 5;
		count++;
	}
	


}
void HighScoreState::SortByScore()
{
	for (unsigned int i = 1; i < scores.size(); i++)
	{
		int next = i;
		while (next > 0 && scores[next - 1].waves < scores[next].waves)
		{
			HighScore temp = scores[next];
			scores[next] = scores[next - 1];
			scores[next - 1] = temp;
			next--;
		}
	}
}