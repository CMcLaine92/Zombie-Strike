#define NUM_CHOICES		4
#define SAVE_FILE		"OptionsVolumes.txt"

#include "OptionsState.h"

#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"
#include <fstream>
#include "Game.h"
#include "BitmapFont.h"
#include "MainMenuState.h"


/**************************************************************/
// GetInstance
/*static*/ OptionsState* OptionsState::GetInstance( void )
{
	static OptionsState s_Instance;

	return &s_Instance;
}


/**************************************************************/
// Enter
/*virtual*/ void OptionsState::Enter( void )
{
	// Reset the cursor to the top (commented out to keep the last cursor position)
	m_nCursor = 0;

	
	// Set background color
	SGD::GraphicsManager::GetInstance()->SetClearColor( {50, 50, 50} );	// black


	// Load assets
	SGD::AudioManager* pAudio	= SGD::AudioManager::GetInstance();

	m_hBackgroundSFX			= pAudio->LoadAudio(L"resource/audio/shotgun_fire.wav");

}

/**************************************************************/
// Exit
/*virtual*/ void OptionsState::Exit( void )
{
	SaveVolumes();

	// Unload assets
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	if (pAudio->IsAudioPlaying(m_hBackgroundSFX) == true)
		pAudio->StopAudio(m_hBackgroundSFX);

	pAudio->UnloadAudio(m_hBackgroundSFX);
}


/**************************************************************/
// Input
/*virtual*/ bool OptionsState::Input( void )
{
	SGD::GraphicsManager*	pGraphics	= SGD::GraphicsManager::GetInstance();
	SGD::AudioManager*		pAudio		= SGD::AudioManager::GetInstance();
	SGD::InputManager*		pInput		= SGD::InputManager::GetInstance();


	// Press Escape to quit
	if (pInput->IsKeyPressed(SGD::Key::Escape) == true || (m_nCursor == (NUM_CHOICES - 1) && pInput->IsKeyPressed(SGD::Key::Enter) == true) ||
		pInput->IsButtonPressed(0, 2) == true || (m_nCursor == (NUM_CHOICES - 1) && pInput->IsButtonReleased(0, 1) == true))
		Game::GetInstance()->RemoveState();



	if (pInput->IsKeyPressed(SGD::Key::Down) == true || pInput->IsDPadPressed(0, SGD::DPad::Down) == true)
		m_nCursor = m_nCursor + 1 < NUM_CHOICES ? m_nCursor + 1 : 0;
	else if (pInput->IsKeyPressed(SGD::Key::Up) == true || pInput->IsDPadPressed(0, SGD::DPad::Up) == true)
		m_nCursor = m_nCursor - 1 >= 0 ? m_nCursor - 1 : NUM_CHOICES - 1;

	

	int volumes[2];
	volumes[0] = pAudio->GetMasterVolume(SGD::AudioGroup::Music);
	volumes[1] = pAudio->GetMasterVolume(SGD::AudioGroup::SoundEffects);

	int volOffset = 10;	// int volMin = 0, volMax = 100;
	switch (m_nCursor)
	{
	case 0: // Music
		{
			if (pInput->IsKeyPressed(SGD::Key::Right) == true || pInput->IsDPadPressed(0, SGD::DPad::Right) == true)
				volumes[0] += volOffset;
			else if (pInput->IsKeyPressed(SGD::Key::Left) == true || pInput->IsDPadPressed(0, SGD::DPad::Left) == true)
				volumes[0] -= volOffset;
		}
		break;

	case 1: // Sfx
		{
			if (pInput->IsKeyPressed(SGD::Key::Right) == true || pInput->IsDPadPressed(0, SGD::DPad::Right) == true)
				volumes[1] += volOffset;
			else if (pInput->IsKeyPressed(SGD::Key::Left) == true || pInput->IsDPadPressed(0, SGD::DPad::Left) == true)
				volumes[1] -= volOffset;
		}
		break;

	case 2: // full screen
		{
			if (pInput->IsKeyPressed(SGD::Key::Right) == true || pInput->IsKeyPressed(SGD::Key::Left) == true ||
				pInput->IsDPadPressed(0, SGD::DPad::Right) == true || pInput->IsDPadPressed(0, SGD::DPad::Left) == true)
			{
				m_bFullScreen = !m_bFullScreen;

				float screenW = Game::GetInstance()->GetScreenWidth();
				float screenH = Game::GetInstance()->GetScreenHeight();

				if (m_bFullScreen == false)
					pGraphics->Resize(SGD::Size(screenW, screenH), true);
				else
					pGraphics->Resize(SGD::Size(screenW, screenH), false);
			}
		}
		break;
	}


	pAudio->SetMasterVolume(SGD::AudioGroup::Music, volumes[0]);
	pAudio->SetMasterVolume(SGD::AudioGroup::SoundEffects, volumes[1]);



	// keep playing
	return true;
}


/**************************************************************/
// Update
/*virtual*/ void OptionsState::Update( float elapsedTime )
{
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	// music
	if (m_nCursor == 0)
	{
		if (pAudio->IsAudioPlaying(m_hBackgroundSFX) == true)
			pAudio->StopAudio(m_hBackgroundSFX);
	}

	// sfx
	else if (m_nCursor == 1)
	{
		if (pAudio->IsAudioPlaying(m_hBackgroundSFX) == false)
			pAudio->PlayAudio(m_hBackgroundSFX, true);
	}

	// full screen
	else if (m_nCursor == 2)
	{
		if (pAudio->IsAudioPlaying(m_hBackgroundSFX) == true)
			pAudio->StopAudio(m_hBackgroundSFX);
	}
}


/**************************************************************/
// Render
/*virtual*/ void OptionsState::Render( void )
{
	SGD::AudioManager*		pAudio		= SGD::AudioManager::GetInstance();


	// Use the game's font
	const BitmapFont* pFont = Game::GetInstance()->GetFont();


	// Align text based on window width
	float width = Game::GetInstance()->GetScreenWidth();


	// Display the title centered at 4x scale
	pFont->Draw("OPTIONS", { (width - (7 * 32 * 4.0f)) / 2, 50 }, 3.0f, { 255, 255, 255 });


	// Align text based on window width
	float left_start	= 50.0F;				// 50
	float right_start	= width - 224.0F;		// 800
	float starting_y	= 200.0F;
	float offset		= 50.0F;
	float scale			=1.25f;


	SGD::OStringStream volumes[2];
	volumes[0] << pAudio->GetMasterVolume(SGD::AudioGroup::Music);
	volumes[1] << pAudio->GetMasterVolume(SGD::AudioGroup::SoundEffects);


	pFont->Draw("Music", { left_start, 250.0F }, scale, { 255, 0, 0 });
	pFont->Draw("Volume", { left_start + 100.0F, 300.0F }, scale, { 255, 0, 0 });

	pFont->Draw("Sound Effects", { left_start, 400.0F }, scale, { 255, 0, 0 });
	pFont->Draw("Volume", { left_start + 100.0F, 450.0F }, scale, { 255, 0, 0 });
	pFont->Draw("Full Screen", { (width - (11 * 32 * scale)) / 2, 550.0F }, scale, { 255, 0, 0 });

	switch (m_nCursor)
	{
	case 0:
		pFont->Draw(volumes[0].str().c_str(), { left_start + 600.0F, 300.0F }, scale, { 255, 255, 255 });
		pFont->Draw(volumes[1].str().c_str(), { left_start + 600.0F, 450.0F }, scale, { 255, 0, 0 });

		if (m_bFullScreen == true)
			pFont->Draw("ON", { (width - (2 * 32 * scale)) / 2, 600.0F }, scale, { 255, 0, 0 });
		else
			pFont->Draw("OFF", { (width - (3 * 32 * scale)) / 2, 600.0F }, scale, { 255, 0, 0 });


		pFont->Draw("Back", { left_start, 700.0F }, 1.0f, { 255, 0, 0 });

		break;
	
	case 1:
		pFont->Draw(volumes[0].str().c_str(), { left_start + 600.0F, 300.0F }, scale, { 255, 0, 0 });
		pFont->Draw(volumes[1].str().c_str(), { left_start + 600.0F, 450.0F }, scale, { 255, 255, 255 });

		if (m_bFullScreen == true)
			pFont->Draw("ON", { (width - (2 * 32 * scale)) / 2, 600.0F }, scale, { 255, 0, 0 });
		else
			pFont->Draw("OFF", { (width - (3 * 32 * scale)) / 2, 600.0F }, scale, { 255, 0, 0 });


		pFont->Draw("Back", { left_start, 700.0F }, 1.0f, { 255, 0, 0 });

		break;
	case 2:
		pFont->Draw(volumes[0].str().c_str(), { left_start + 600.0F, 300.0F }, scale, { 255, 0, 0 });
		pFont->Draw(volumes[1].str().c_str(), { left_start + 600.0F, 450.0F }, scale, { 255, 0, 0 });

		if (m_bFullScreen == true)
			pFont->Draw("ON", { (width - (2 * 32 * scale)) / 2, 600.0F }, scale, { 255, 255, 255 });
		else
			pFont->Draw("OFF", { (width - (3 * 32 * scale)) / 2, 600.0F }, scale, { 255, 255, 255 });


		pFont->Draw("Back", { left_start, 700.0F }, 1.0f, { 255, 0, 0 });

		break;
	case 3:
		pFont->Draw(volumes[0].str().c_str(), { left_start + 600.0F, 300.0F }, scale, { 255, 0, 0 });
		pFont->Draw(volumes[1].str().c_str(), { left_start + 600.0F, 450.0F }, scale, { 255, 0, 0 });

		if (m_bFullScreen == true)
			pFont->Draw("ON", { (width - (2 * 32 * scale)) / 2, 600.0F }, scale, { 255, 0, 0 });
		else
			pFont->Draw("OFF", { (width - (3 * 32 * scale)) / 2, 600.0F }, scale, { 255, 0, 0 });


		pFont->Draw("Back", { left_start, 700.0F }, 1.0f, { 255, 255, 255 });

		break;
	}
	

	//const char* output = "=                          =";
	//SGD::Point position;

	//// music & sfx
	//position.x = (left_start + 100.0F) - 50.0F;
	//position.y = 300.0F + (150.0f * m_nCursor);



	//// full screen
	//if (m_nCursor == 2)
	//{
	//	output		= m_bFullScreen == true ? "=  =" : "=    =";
	//	int length	= m_bFullScreen == true ? 4 : 5;

	//	position.x	= (width - (length * 32 * scale)) * 0.5f;
	//	position.y	= 600.0F;
	//}
	//else if (m_nCursor == 3)
	//{
	//	output		= "=     =";
	//	position.x	= left_start - 40.0F;
	//	position.y	= 700.0F;
	//}

	//pFont->Draw( output, position, 1.0f, {255, 0, 0} );
}


/**************************************************************/
// LoadVolumes
void OptionsState::LoadVolumes( void ) const
{
	// File Input
	std::ifstream load(SAVE_FILE, std::ios_base::in);
	if (load.is_open())
	{
		// Load volumes
		int musicvol, sfxvol;
		load >> musicvol >> sfxvol;
		load.ignore(INT_MAX, '\n');


		// Set volumes
		SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::Music, musicvol);
		SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::SoundEffects, sfxvol);


		// Close
		load.close();
	}
}


/**************************************************************/
// SaveVolumes
void OptionsState::SaveVolumes( void ) const
{
	std::ofstream save(SAVE_FILE, std::ios_base::out/* | std::ios_base::trunc*/);
	if (save.is_open())
	{
		// Store volumes
		int musicvol, sfxvol;
		musicvol	= SGD::AudioManager::GetInstance()->GetMasterVolume(SGD::AudioGroup::Music);
		sfxvol		= SGD::AudioManager::GetInstance()->GetMasterVolume(SGD::AudioGroup::SoundEffects);


		// Save volumes
		save << musicvol << '\t' << sfxvol << '\n';


		// Close
		save.close();
	}
}


