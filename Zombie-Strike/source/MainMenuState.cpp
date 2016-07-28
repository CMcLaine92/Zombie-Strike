#define NUM_CHOICES		6

#include "MainMenuState.h"

#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"

#include "Game.h"
#include "BitmapFont.h"
#include "GameplayState.h"
#include "PickSaveSlotState.h"
#include "HowToPlayState.h"
#include "CreditsState.h"
#include "OptionsState.h"
#include "ShopState.h"
#include "IntroState.h"
#include "HTPGameState.h"

#include "../SGD Wrappers/SGD_EventManager.h"

/**************************************************************/
// GetInstance
//	- store the ONLY instance in global memory
//	- return the only instance by pointer
/*static*/ MainMenuState* MainMenuState::GetInstance( void )
{
	static MainMenuState s_Instance;

	return &s_Instance;
}


/**************************************************************/
// Enter
//	- reset the game & load resources
/*virtual*/ void MainMenuState::Enter( void )
{
	SGD::GraphicsManager*	pGraphics	= SGD::GraphicsManager::GetInstance();
	SGD::AudioManager*		pAudio		= SGD::AudioManager::GetInstance();
	SGD::InputManager*		pInput		= SGD::InputManager::GetInstance();


	// Reset the cursor to the top (comment out to keep the last cursor position)
	//m_nCursor = 0;
	clicked		= false;
	selected	= false;
	//pInput->CheckForNewControllers();

	starting_x = Game::GetInstance()->GetScreenWidth() * .10f;
	starting_y = Game::GetInstance()->GetScreenHeight() * .2f;


	// Load assets
	m_hBackgroundImage	= pGraphics->LoadTexture("resource/graphics/MenuImages/Zombie_Strike_menu_image.png");
	m_hTitleImage		= pGraphics->LoadTexture("resource/graphics/MenuImages/Zombie_Strike_menu_title.png");
	m_hReticleImage		= pGraphics->LoadTexture("resource/graphics/MenuImages/Reticle3.png", { 0, 0, 0 });

	m_hButton2			= pGraphics->LoadTexture("resource/graphics/MenuImages/rectangle2.png");
	m_hLightning		= pGraphics->LoadTexture("resource/graphics/MenuImages/lightning2.png");

	m_hButtonSwitchSFX	= pAudio->LoadAudio("resource/audio/button_switch.wav");
	m_hMenuChangeSFX	= pAudio->LoadAudio("resource/audio/menu_change.wav");

	//COMMENT BACK IN WHEN FILES ARE ADDED
	//m_hMainTheme = pAudio->LoadAudio("resource/audio/zstrikemain.xwm");
	//m_hSurvivalTheme = pAudio->LoadAudio("resource/audio/zstrikesurvival.xwm");

	// Load volume levels
	OptionsState::GetInstance()->LoadVolumes();


	// setup selection rects
	selectonrects	= new SGD::Rectangle[NUM_CHOICES];
	stringlengths	= new int[NUM_CHOICES];

	int lengths[NUM_CHOICES] = { 9, 11, 7, 7, 4 };

	for (size_t i = 0; i < NUM_CHOICES; i++)
		stringlengths[i] = lengths[i];

	float x_offset = 16.0f;
	float y_offset = 15.0f;

	for (size_t i = 0; i < NUM_CHOICES; i++)
	{
		selectonrects[i].left	= starting_x;
		selectonrects[i].left	-= x_offset;

		selectonrects[i].top	= starting_y + (vertical_offset * i);
		selectonrects[i].top	-= y_offset;

		selectonrects[i].right	= selectonrects[i].left + 256.0f;
		//selectonrects[i].right	+= x_offset;

		selectonrects[i].bottom = selectonrects[i].top + 32.0f;
		selectonrects[i].bottom	+= y_offset * 2;
	}

	fadeTime.AddTime(.25f);
	lightningTime.AddTime(3);
	lFlashTime.AddTime(.01f);
}


/**************************************************************/
// Exit
//	- deallocate / unload resources
/*virtual*/ void MainMenuState::Exit( void )
{
	SGD::GraphicsManager* pGraphics	= SGD::GraphicsManager::GetInstance();
	SGD::AudioManager*	  pAudio	= SGD::AudioManager::GetInstance();

	// Unload assets
	pGraphics->UnloadTexture(m_hBackgroundImage);
	pGraphics->UnloadTexture(m_hTitleImage);
	pGraphics->UnloadTexture(m_hReticleImage);
	//pGraphics->UnloadTexture(m_hButton1);
	pGraphics->UnloadTexture(m_hButton2);
	pGraphics->UnloadTexture(m_hLightning);

	pAudio->UnloadAudio(m_hButtonSwitchSFX);
	pAudio->UnloadAudio(m_hMenuChangeSFX);

	//pAudio->UnloadAudio(m_hMainTheme);
	//pAudio->UnloadAudio(m_hSurvivalTheme);

	// deallocate dynamic arrays
	delete[] selectonrects;
	delete[] stringlengths;

	selectonrects = nullptr;
	stringlengths = nullptr;

}


/**************************************************************/
// Input
//	- handle user input
/*virtual*/ bool MainMenuState::Input( void )
{
	SGD::InputManager*	pInput	= SGD::InputManager::GetInstance();
	SGD::AudioManager*	pAudio	= SGD::AudioManager::GetInstance();

	m_mPrevious = m_nCursor;


	// Press Escape to quit
	if( pInput->IsKeyPressed( SGD::Key::Escape ) == true/* || pInput->IsButtonPressed(0, 2) == true */)
		m_nCursor = MenuItems::EXIT;


	// Input: keyboard & D-pad
	if (pInput->IsKeyPressed(SGD::Key::Down) == true || pInput->IsDPadPressed(0, SGD::DPad::Down) == true)
	{
		m_mPrevious = m_nCursor;
		m_nCursor = m_nCursor + 1 < NUM_CHOICES ? m_nCursor + 1 : 0;
	}
	else if (pInput->IsKeyPressed(SGD::Key::Up) == true || pInput->IsDPadPressed(0, SGD::DPad::Up) == true)
	{
		m_mPrevious = m_nCursor;
		m_nCursor = m_nCursor - 1 >= 0 ? m_nCursor - 1 : NUM_CHOICES - 1;
	}


	// Input: L1 - Left Joystick
	if (pInput->GetLeftJoystick(0).x != 0 || pInput->GetLeftJoystick(0).y != 0)
	{
		SGD::Point	mpoint		= pInput->GetMousePosition();
		SGD::Vector	joystick	= pInput->GetLeftJoystick(0);
		float		stickmin	= 0.250f;
		float		mousevel	= 1.0f;


		if (joystick.x > stickmin)
			mpoint.x += mousevel;
		else if (joystick.x < stickmin * -1.0f)
			mpoint.x -= mousevel;
		
		if (joystick.y > stickmin)
			mpoint.y += mousevel;
		else if (joystick.y < stickmin * -1.0f)
			mpoint.y -= mousevel;

		if (mpoint.x < 0.0F)
			mpoint.x = 0.0F;
		if (mpoint.y < 0.0F)
			mpoint.y = 0.0F;
		if (mpoint.x > Game::GetInstance()->GetScreenWidth())
			mpoint.x = Game::GetInstance()->GetScreenWidth();
		if (mpoint.y > Game::GetInstance()->GetScreenHeight())
			mpoint.y = Game::GetInstance()->GetScreenHeight();

		pInput->SetMousePosition(mpoint);
	}


	// Input: Mouse
	SGD::Point mousepos = pInput->GetMousePosition();
	bool collided = false;
	for (size_t i = 0; i < NUM_CHOICES; i++)
	{
		if (mousepos.IsWithinRectangle(selectonrects[i]) == true)
		{
			m_mPrevious	= m_nCursor;
			m_nCursor	= i;
			collided	= true;
		}
	}

	selected = collided;

	clicked = pInput->IsKeyDown(SGD::Key::LButton) == true ? true : false;
	/*
	if (pInput->IsKeyDown(SGD::Key::LButton) == true)
		clicked = true;
	else
		clicked = false;
	*/

	if (m_mPrevious != m_nCursor)
	{
		if (pAudio->IsAudioPlaying(m_hButtonSwitchSFX) == false)
			pAudio->PlayAudio(m_hButtonSwitchSFX, false);
	}



	// Selection
	if (pInput->IsKeyPressed(SGD::Key::Enter) == true || (pInput->IsKeyReleased(SGD::Key::LButton) == true && selected == true) || pInput->IsButtonPressed(0, 1) == true)
	{
		if (pAudio->IsAudioPlaying(m_hMenuChangeSFX) == false)
			pAudio->PlayAudio(m_hMenuChangeSFX, false);

		switch (m_nCursor)
		{
		case MenuItems::STORY_MODE:
			{
				GameplayState::GetInstance()->SetGameMode(true);

				Game::GetInstance()->AddState(PickSaveSlotState::GetInstance());
				return true;
			}
			break;


		case MenuItems::SURVIVAL_MODE:
			{
				GameplayState::GetInstance()->SetGameMode(false);
				Game::GetInstance()->AddState(PickSaveSlotState::GetInstance());
				return true;
			}
			break;


		case MenuItems::HOW_TO_PLAY:
			{
				Game::GetInstance()->AddState(HowToPlayState::GetInstance());
				return true;
			}
			break;


		case MenuItems::OPTIONS:
			{
				Game::GetInstance()->AddState(OptionsState::GetInstance());
				return true;
			}
			break;


		case MenuItems::CREDITS:
			{
				Game::GetInstance()->AddState(CreditsState::GetInstance());
				return true;
			}
			break;


		case MenuItems::EXIT:
			{
				return false;	// quit the game
			}
			break;
		}
	}
	/*
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::LButton) == true)
	{
		if (m_nCursor == MenuItems::PLAY_GAME)
		{
			Game::GetInstance()->RemoveState();
			Game::GetInstance()->AddState(GameplayState::GetInstance());
			return true;
		}
		else if (m_nCursor == MenuItems::PLAY_GAME)
		{
			Game::GetInstance()->AddState(HowToPlayState::GetInstance());
			return true;
		}
		else if (mousepos.IsWithinRectangle(selectonrects[MenuItems::OPTIONS]) == true)
		{
			Game::GetInstance()->AddState(OptionsState::GetInstance());
			return true;
		}
		else if (mousepos.IsWithinRectangle(selectonrects[MenuItems::CREDITS]) == true)
		{
			Game::GetInstance()->AddState(CreditsState::GetInstance());
			return true;
		}
		else if (mousepos.IsWithinRectangle(selectonrects[MenuItems::EXIT]) == true)
		{
			return false;	// quit the game
		}
	}
	*/





	// keep playing
	return true;
}


/**************************************************************/
// Update
//	- update entities / animations
/*virtual*/ void MainMenuState::Update( float elapsedTime )
{
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	//COMMENT BACK IN WHEN AUDIO IS ADDED
	if (m_nCursor == 1 && pAudio->IsAudioPlaying(Game::GetInstance()->m_hSurvivalTheme) == false)
	{
		pAudio->StopAudio(Game::GetInstance()->m_hMainTheme);
		pAudio->PlayAudio(Game::GetInstance()->m_hSurvivalTheme, true);
	}
	if (m_nCursor != 1 && pAudio->IsAudioPlaying(Game::GetInstance()->m_hMainTheme) == false)
	{
		pAudio->StopAudio(Game::GetInstance()->m_hSurvivalTheme);
		pAudio->PlayAudio(Game::GetInstance()->m_hMainTheme, true);
	}

	if (m_nCursor == 1)
	{
		if (fadeTime.GetTime() <= 0.0f && trans != 160 && mTrans != 0)
		{
			trans += 5;
			mTrans -= 5;
			fadeTime.AddTime(0.05f);
		}

		fadeTime.Update(elapsedTime);
	}

	else
	{
		if (fadeTime.GetTime() <= 0.0f && trans != 0 && mTrans != 175)
		{
			trans -= 5;
			mTrans += 5;
			fadeTime.AddTime(0.05f);
		}



		fadeTime.Update(elapsedTime);
	}

	if (lightningTime.GetTime() < .5f && lTrans != 50)
	{
		if (lFlashTime.GetTime() <= 0.0f)
		{
			lTrans += 10;
			lFlashTime.AddTime(.025f);
		}

		lFlashTime.Update(elapsedTime);
	}

	if (lightningTime.GetTime() <= 0.0f)
	{
		rand();
		lightningTime.AddTime((float)(rand()% 5 + 3));
		lTrans = 0;

	}

	if (lTrans >= 50)
	{
		lTrans = 0;
	}

	lightningTime.Update(elapsedTime);
}


/**************************************************************/
// Render
//	- render entities / menu options
/*virtual*/ void MainMenuState::Render( void )
{
	SGD::GraphicsManager*	pGraphics	= SGD::GraphicsManager::GetInstance();
	SGD::InputManager*		pInput		= SGD::InputManager::GetInstance();


	// Draw the background image
	pGraphics->DrawTexture(m_hBackgroundImage, { 0, 0 });

	if (lTrans > 0)
	{
		pGraphics->DrawTexture(m_hLightning, { 375, 0 }, 0.0f, {},{100,200,200,200}, {-1.0f,.5f});
		pGraphics->DrawTexture(m_hLightning, { Game::GetInstance()->GetScreenWidth() * .65f, 0 }, 0.0f, {}, { 100, 200, 200, 200 }, { 1.0f, .5f });
	}

	SGD::Color sColor(trans, 100, 0, 0);
	SGD::Color mColor(mTrans, 50, 0, 50);
	SGD::Color lColor(lTrans, 200, 200, 255);

	pGraphics->DrawRectangle({ 0, 0, Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() }, sColor);
	pGraphics->DrawRectangle({ 0, 0, Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() }, mColor);
	pGraphics->DrawRectangle({ 0, 0, Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() }, lColor);

	// Draw the buttons
	for (size_t i = 0; i < NUM_CHOICES; i++)
		pGraphics->DrawTexture(m_hButton2, selectonrects[i].GetTopLeft(), 0.0f, {}, {155,155,155}, { 1.0f, 1.0f });


	// Use the game's font
	const BitmapFont* pFont = Game::GetInstance()->GetFont();
	const BitmapFont* pFont2 = Game::GetInstance()->GetShopFont();



	// Draw the game title
	// Align text based on window width
	float screenWidth			= Game::GetInstance()->GetScreenWidth();
	float screenHeight = Game::GetInstance()->GetScreenHeight();

	float titlescale	= .75f;
	pGraphics->DrawTexture(m_hTitleImage, { screenWidth * 0.2f, -(screenHeight * 0.09375f)* titlescale }, 0.0f, {},{ 200, 150, 0, 150 }, { titlescale, titlescale });

	// Display the menu options centered at 1x scale
	std::string menuitems[NUM_CHOICES] = { "Story Mode", "Survival Mode", "How to Play", "Options", "Credits", "Exit" };

	float offset = 100.0F;

	for (size_t i = 0; i < NUM_CHOICES; i++)
	{
		SGD::Color clr_normal	= { 255, 255, 0, 0 };		// red
		SGD::Color clr_selected = { 255, 255, 255, 255 };	// white
		SGD::Color clr_held		= { 255, 0, 0, 0 };			// black


		// not selected or colliding
		if (m_nCursor != i)
			pFont->Draw(menuitems[i].c_str(), { starting_x, starting_y + (vertical_offset * i) }, text_scale, clr_normal);


		// selected, not clicked, colliding
		else if (m_nCursor == i && clicked == false && selected == true)
			pFont->Draw(menuitems[i].c_str(), { starting_x, starting_y + (vertical_offset * i) }, text_scale, clr_selected);


		// selected, clicked, colliding
		else if (m_nCursor == i && clicked == true && selected == true)
			pFont->Draw(menuitems[i].c_str(), { starting_x, starting_y + (vertical_offset * i) }, text_scale, clr_held);


		// selected, clicked, not colliding
		else if (m_nCursor == i && clicked == true && selected == false)
			pFont->Draw(menuitems[i].c_str(), { starting_x, starting_y + (vertical_offset * i) }, text_scale, clr_selected);


		// selected, not clicked, not colliding
		else if (m_nCursor == i && clicked == false && selected == false)
			pFont->Draw(menuitems[i].c_str(), { starting_x, starting_y + (vertical_offset * i) }, text_scale, clr_selected);
	}




	// Draw the reticle
	SGD::Point	retpos		= pInput->GetMousePosition();
	float		retscale	= 0.8f;

	retpos.Offset(-32.0F * retscale, -32.0F * retscale);
	pGraphics->DrawTexture(m_hReticleImage, retpos, 0.0F, {}, { 255, 255, 255 }, { retscale, retscale });


}
