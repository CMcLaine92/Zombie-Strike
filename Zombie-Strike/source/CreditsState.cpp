#define SCROLL_SPEED		75.0f//47.0F

#include "CreditsState.h"

#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"

#include "Game.h"
#include "BitmapFont.h"
#include "MainMenuState.h"


/**************************************************************/
// GetInstance
/*static*/ CreditsState* CreditsState::GetInstance( void )
{
	static CreditsState s_Instance;

	return &s_Instance;
}


/**************************************************************/
// Enter
/*virtual*/ void CreditsState::Enter( void )
{	
	// Set background color
	SGD::GraphicsManager::GetInstance()->SetClearColor( {0, 0, 0} );	// black


	starting_y = Game::GetInstance()->GetScreenHeight() + 80.0F;// +20.0F;// * 15.0F;// + 170.0F;



}

/**************************************************************/
// Exit
/*virtual*/ void CreditsState::Exit( void )
{
}


/**************************************************************/
// Input
/*virtual*/ bool CreditsState::Input( void )
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();


	// Press Escape to quit
	if (pInput->IsKeyPressed(SGD::Key::Escape) == true || pInput->IsKeyPressed(SGD::Key::Enter) == true || pInput->IsButtonDown(0, 2) == true)
	{
		Game::GetInstance()->RemoveState();
		//Game::GetInstance()->AddState(MainMenuState::GetInstance());
	}


	return true;
}


/**************************************************************/
// Update
/*virtual*/ void CreditsState::Update( float elapsedTime )
{
	if (starting_y <= -700.0f)
	{
		Game::GetInstance()->RemoveState();
		//Game::GetInstance()->AddState(MainMenuState::GetInstance());
	}

	starting_y -= SCROLL_SPEED * elapsedTime;

	//if (starting_y < 120.0f)
	//	starting_y = 120.0f;
}


/**************************************************************/
// Render
/*virtual*/ void CreditsState::Render( void )
{
	// Use the game's font
	const BitmapFont* pFont = Game::GetInstance()->GetFont();

	// Align text based on window width
	float width = Game::GetInstance()->GetScreenWidth();


	// Display the title centered at 4x scale
	//pFont->Draw("CREDITS", { (width - (7 * 32 * 3.0f)) / 2, 10 }, 3.0f, { 255, 255, 255 });
	pFont->Draw("CREDITS", { (width - (7 * 32 * 3.0f)) / 2, starting_y - (32 * 3.0f) }, 3.0f, { 255, 255, 255 });


	// Align text based on window width
	float left_start		= width * 0.15f;
	float y_offset			= 210.0f;
	float scale				= 1.0f;
	float newline_offset	= 31.0f;



	// variables to use as a buffer for strings on the same line
	// will be CONSTANTLY given new values based on: current line & string, etc....
	float		x_offset_var	= left_start;
	std::string	string_var		= "";
	int			num_newlines	= 0;


	//std::string developers = "Developers: Ctrl the Source (formerly Gold Nugget Games)\n\tConner McLaine\n\tJoshua Griggs\n\tJason  Bloomfield\n\n";
	#pragma region Developers
	std::string developers1 = "Developers: CTRL the Source ";
	std::string developers2 = "(formerly Gold Nugget Games)";
	std::string developers3 = "\n\tConner McLaine\n\tJoshua Griggs\n\tJason  Bloomfield\n\n";

	string_var = developers1 + developers2;

	pFont->Draw(string_var.c_str(), { left_start, starting_y }, scale, { 255, 255, 0 });
	pFont->Draw(developers1.c_str(), { left_start, starting_y }, scale, { 0, 255, 0 });
	pFont->Draw(developers3.c_str(), { left_start, starting_y }, scale, { 255, 0, 0 });
	#pragma endregion


	//std::string eps = "Executive Producers:\n\tSteve   VanZandt\n\tJohn OLeske\n\n";
	#pragma region Executive Producers
	num_newlines += 5;
	std::string eps1 = "Executive Producers:";
	std::string eps2 = "\n\tSteve VanZandt\n\tJohn OLeske\n\n";

	string_var = eps1 + eps2;

	pFont->Draw(string_var.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 0, 255, 0 });
	pFont->Draw(eps2.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 255, 0, 0 });
	#pragma endregion


	//std::string aps = "Associate Producers:\n\tRobert Martinez\n\tSean   Hathaway\n\tShawn  Paris";
	#pragma region Associate Producers
	num_newlines += 4;
	std::string aps1 = "Associate Producers:";
	std::string aps2 = "\n\tRobert Martinez\n\tSean Hathaway\n\tShawn Paris\n\n";

	string_var = aps1 + aps2;

	pFont->Draw(string_var.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 0, 255, 0 });
	pFont->Draw(aps2.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 255, 0, 0 });
	#pragma endregion


	//std::string artists = "Artists:\n\tCaris   Frazier\n\tGregory Bay\n\n";
	#pragma region Artists
	num_newlines += 5;
	std::string artists1 = "Artists:";
	std::string artists2 = "\n\tCaris Frazier\n\tGregory Bay\n\n";

	string_var = artists1 + artists2;

	pFont->Draw(string_var.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 0, 255, 0 });
	pFont->Draw(artists2.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 255, 0, 0 });
	#pragma endregion


	//std::string assets = "Assets & Resources:\n\tWestar Music\n\tSpriters-resource.com\n\tSounds-resource.com\n\tDafont.com\n\n";
	#pragma region Assets & Resources
	num_newlines += 4;
	std::string assets1 = "Assets & Resources:";
	std::string assets2 = "\n\tWestar Music\n\tSpriters-resource.com\n\tSounds-resource.com\n\tDafont.com\n\n";

	string_var = assets1 + assets2;

	pFont->Draw(string_var.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 0, 255, 0 });
	pFont->Draw(assets2.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 255, 0, 0 });
	#pragma endregion



}
