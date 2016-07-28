#define NUM_CHOICES		2

#include "LoseGameState.h"
#include "HighScoreState.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"
#include "../SGD Wrappers/SGD_Event.h"

#include "Game.h"
#include "BitmapFont.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include <fstream>
#include "Player.h"
#include "SpawnManager.h"

/**************************************************************/
// GetInstance
/*static*/ LoseGameState* LoseGameState::GetInstance( void )
{
	static LoseGameState s_Instance;

	return &s_Instance;
}


/**************************************************************/
// Enter
/*virtual*/ void LoseGameState::Enter( void )
{
	// Set background color
	SGD::GraphicsManager::GetInstance()->SetClearColor( {0, 0, 0} );	// black
	m_nCursor = 0;

	// Load assets
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	m_hBackgroundImage	= pGraphics->LoadTexture("resource/graphics/MenuImages/youLose.png");
}


/**************************************************************/
// Exit
/*virtual*/ void LoseGameState::Exit( void )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();


	// Unload assets
	pGraphics->UnloadTexture(m_hBackgroundImage);

}


/**************************************************************/
// Input
/*virtual*/ bool LoseGameState::Input( void )
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (GameplayState::GetInstance()->GetGameMode() == true)
	{
		if (pInput->IsKeyPressed(SGD::Key::Down) == true || pInput->IsDPadPressed(0, SGD::DPad::Down) == true)
			m_nCursor = m_nCursor + 1 < NUM_CHOICES ? m_nCursor + 1 : 0;
		else if (pInput->IsKeyPressed(SGD::Key::Up) == true || pInput->IsDPadPressed(0, SGD::DPad::Up) == true)
			m_nCursor = m_nCursor - 1 >= 0 ? m_nCursor - 1 : NUM_CHOICES - 1;

		if (pInput->IsKeyPressed(SGD::Key::Enter) == true || pInput->IsButtonPressed(0, 1) == true)
		{
			switch (m_nCursor)
			{
			case 0: // gameplay
			{
						SGD::Event msg("UNPAUSE");
						msg.SendEventNow();
						Game::GetInstance()->RemoveState();
						Game::GetInstance()->RemoveState();
						Game::GetInstance()->AddState(GameplayState::GetInstance());
						return true;
			}
				break;


			case 1: // main menu
			{
						Game::GetInstance()->RemoveState();
						Game::GetInstance()->RemoveState();
						Game::GetInstance()->AddState(MainMenuState::GetInstance());
						return true;
			}
				break;
			}
		}
	}
	else
	{
		
		if (scoreGiven == false)
		{
			if (initials.length() < 4)
			{
				wchar_t ch = pInput->GetAnyCharPressed();
				if (ch != '\0' && ch != '\r' && ch != '\t' && ch != ' ' && ch != '\b' && initials.length() < 3)
					initials += toupper(ch);
				else if (ch == '\b' && initials.empty() == false)
					initials.erase(initials.length() - 1);

			}
		
			if ((pInput->IsKeyPressed(SGD::Key::Enter) == true ||  pInput->IsButtonPressed(0, 1) == true) && initials.length() > 0)
			{
				Player* player = dynamic_cast<Player*>(GameplayState::GetInstance()->GetPlayer());
				std::wofstream fout;
				fout.open("resource/config/highscores.txt", std::ios_base::app);

				if (fout.is_open())
				{
					
					fout << initials.c_str() << '\t' << Game::GetInstance()->GetSurvivalProfile().wavesComplete << '\n';


				}
				fout.close();
				scoreGiven = true;
				Game::GetInstance()->AddState(HighScoreState::GetInstance());

			}
		}
		else
		{
			if (pInput->IsKeyPressed(SGD::Key::Down) == true)
				m_nCursor = m_nCursor + 1 < NUM_CHOICES ? m_nCursor + 1 : 0;
			else if (pInput->IsKeyPressed(SGD::Key::Up) == true)
				m_nCursor = m_nCursor - 1 >= 0 ? m_nCursor - 1 : NUM_CHOICES - 1;

			if (pInput->IsKeyPressed(SGD::Key::Enter) == true)
			{
				switch (m_nCursor)
				{
				case 0: // gameplay
				{
							SGD::Event msg("UNPAUSE");
							msg.SendEventNow();
							Game::GetInstance()->RemoveState();
							Game::GetInstance()->RemoveState();
							Game::GetInstance()->AddState(GameplayState::GetInstance());
							return true;
				}
					break;

				case 1: // main menu
				{
							Game::GetInstance()->RemoveState();
							Game::GetInstance()->RemoveState();
							Game::GetInstance()->AddState(MainMenuState::GetInstance());
							return true;
				}
					break;
				}
			}
		}
	}
	
	


	// keep playing
	return true;
}


/**************************************************************/
// Update
/*virtual*/ void LoseGameState::Update( float elapsedTime )
{
}


/**************************************************************/
// Render
/*virtual*/ void LoseGameState::Render( void )
{
	SGD::GraphicsManager*	pGraphics = SGD::GraphicsManager::GetInstance();


	// Draw the background image
	pGraphics->DrawTexture(m_hBackgroundImage, { -10, -190 });


	// Use the game's font
	const BitmapFont* pFont = Game::GetInstance()->GetFont();

	// Align text based on window width
	float width		= Game::GetInstance()->GetScreenWidth();
	float height	= Game::GetInstance()->GetScreenHeight();
	float scale		= 1.25f;
	

	if (GameplayState::GetInstance()->GetGameMode() == false)
	{
		if (scoreGiven == false)
		{
			pFont->Draw("Enter Intials:", { (width - (9 * 24 * scale)) / 2, height * 0.53F }, scale, { 255, 255, 0 });
			pFont->Draw(initials.c_str(), { (width - (3 * 32 * scale)) / 2, (height * 0.5F) + 100.0f }, scale, { 0, 255, 0 });



			/*const char*	output = m_nCursor == 0 ? "=    =" : "=   =";
			int			length = m_nCursor == 0 ? 3 : 2;
			pFont->Draw(output, { (width - (length * 32)) / 2 - 32.0F, (height * 0.5F) + (100.0f * m_nCursor) + 100.0f }, 1.0f, { 255, 0, 0 });*/
		}
		else
		{
			pFont->Draw("Continue?", { (width - (9 * 24 * scale)) / 2, height * 0.53F }, scale, { 255, 255, 0 });
			pFont->Draw("YES", { (width - (3 * 32 * scale)) / 2, (height * 0.5F) + 100.0f }, scale, { 0, 255, 0 });
			pFont->Draw("NO", { (width - (2 * 32 * scale)) / 2, (height * 0.5F) + 200.0f }, scale, { 0, 255, 0 });


			const char*	output = m_nCursor == 0 ? "=    =" : "=   =";
			int			length = m_nCursor == 0 ? 3 : 2;
			pFont->Draw(output, { (width - (length * 32)) / 2 - 32.0F, (height * 0.5F) + (100.0f * m_nCursor) + 100.0f }, 1.0f, { 255, 0, 0 });

		}
		// Display the text centered
		//pFont->Draw("YOU LOSE!", { (width - (9 * 32 * 3.0f)) / 2, height * 0.25F - (26.0F * 3.0F) }, 3.0f, { 255, 255, 255 });
		//pFont->Draw("GAME OVER!", { (width - (10 * 32 * 3.0f)) / 2, height * 0.25F - (26.0F * 3.0F) }, 3.0f, { 255, 255, 255 });

	}
	else
	{
		pFont->Draw("Continue?", { (width - (9 * 24 * scale)) / 2, height * 0.53F }, scale, { 255, 255, 0 });
		pFont->Draw("YES", { (width - (3 * 32 * scale)) / 2, (height * 0.5F) + 100.0f }, scale, { 0, 255, 0 });
		pFont->Draw("NO", { (width - (2 * 32 * scale)) / 2, (height * 0.5F) + 200.0f }, scale, { 0, 255, 0 });


		const char*	output = m_nCursor == 0 ? "=    =" : "=   =";
		int			length = m_nCursor == 0 ? 3 : 2;
		pFont->Draw(output, { (width - (length * 32)) / 2 - 32.0F, (height * 0.5F) + (100.0f * m_nCursor) + 100.0f }, 1.0f, { 255, 0, 0 });
	}
	

	
}
