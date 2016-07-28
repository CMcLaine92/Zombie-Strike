#include "HowToPlayState.h"

#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"

#include "Game.h"
#include "BitmapFont.h"
#include "MainMenuState.h"


/**************************************************************/
// GetInstance
/*static*/ HowToPlayState* HowToPlayState::GetInstance( void )
{
	static HowToPlayState s_Instance;

	return &s_Instance;
}


/**************************************************************/
// Enter
/*virtual*/ void HowToPlayState::Enter( void )
{
	// Set background color
	SGD::GraphicsManager::GetInstance()->SetClearColor({ 0, 0, 0 });	// black

}


/**************************************************************/
// Exit
/*virtual*/ void HowToPlayState::Exit( void )
{

}


/**************************************************************/
// Input
/*virtual*/ bool HowToPlayState::Input( void )
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();


	// Press Escape to quit
	if (pInput->IsKeyPressed(SGD::Key::Escape) == true || pInput->IsKeyPressed(SGD::Key::Enter) == true || pInput->IsButtonPressed(0, 2) == true)
		Game::GetInstance()->RemoveState();


	return true;
}


/**************************************************************/
// Update
/*virtual*/ void HowToPlayState::Update( float elapsedTime )
{
}


/**************************************************************/
// Render
/*virtual*/ void HowToPlayState::Render( void )
{
	// Use the game's font
	const BitmapFont* pFont = Game::GetInstance()->GetFont();

	// Align text based on window width
	float width = Game::GetInstance()->GetScreenWidth();
	float height = Game::GetInstance()->GetScreenHeight();



	// Display the title centered at 4x scale
	pFont->Draw("How To Play", { (width - (11 * 18 * 2.5f)) / 2, height * 0.10f }, 2.5f, { 255, 255, 255 });


	// Display exit input
	std::string goback = SGD::InputManager::GetInstance()->IsControllerConnected(0) == false
		? "Press 'Esc' to exit"
		: "Press 'O' to exit";
	pFont->Draw(goback.c_str(), { (width - (goback.length() * 25 * 1.0f)) / 2, height * 0.20f  }, 1.0f, { 255, 255, 255 });


	// Align text based on window width
	float left_start	= width * 0.1F;
	float starting_y	= height * 0.3f;
	float y_offset			= 210.0f;
	float scale				= 1.0f;
	float newline_offset	= 31.0f;



	// variables to use as a buffer for strings on the same line
	// will be CONSTANTLY given new values based on: current line & string, etc....
	float		x_offset_var	= left_start;
	std::string	string_var		= "";
	int			num_newlines	= 0;


	//std::string objective = "Objective:\n\tDefeat all the zombies trying to kill you\n\tObtain money to upgrade your weapons and defences\n\n";
	#pragma region Objective
	std::string objective1 = "Objective:";
	std::string objective2 = "\n\tDefeat all the zombies trying to kill you\n\tObtain money to upgrade your weapons and defences\n\n";

	string_var = objective1 + objective2;

	pFont->Draw(string_var.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 255, 0, 0 });
	pFont->Draw(objective2.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 255, 255, 255 });
	#pragma endregion


	if (SGD::InputManager::GetInstance()->IsControllerConnected(0) == false)
	{
		//std::string keycontrols = "Keyboard Controls:\n\nW\t\tMove towards mouse\nS\t\tMove away from mouse\nA\t\tStrafe left\nS\t\tStrafe right\n\n";
		#pragma region Keyboard Controls
		num_newlines += 4;
		std::string keycontrols1 = "Keyboard Controls:";
		std::string keycontrols2 = "\n\n\tW\t\tMove up\n\tS\t\tMove down\n\tA\t\tMove left\n\tS\t\tMove right\n\n\tShift\t\tSprint";
		std::string keycontrols3 = "\n\n\tQ\t\tSwitch to previous weapon\n\tE\t\tSwitch to next weapon\n\tR\t\tReload current weapon\n\tG\t\t Spawn a turret\n\n";
		
		//string_var = keycontrols1 + keycontrols2;
		
		pFont->Draw(keycontrols1.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 255, 0, 0 });
		pFont->Draw(keycontrols2.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 255, 255, 255 });
		pFont->Draw(keycontrols3.c_str(), { left_start, starting_y + (newline_offset * (num_newlines + 5)) }, scale, { 255, 255, 255 });
		#pragma endregion
	}
	else
	{
		//std::string ps3controls = "Keyboard Controls:\n\nW\t\tMove towards mouse\nS\t\tMove away from mouse\nA\t\tStrafe left\nS\t\tStrafe right\n\n";
		#pragma region PS3 Controls
		num_newlines += 4;
		std::string ps3controls1 = "Play Station Controls:";
		std::string ps3controls2 = "\n\n\tLeft Stick\t\tMove player\n\tRight Stick\t\t Rotate player\n\tR2\t\t\tFire weapon\n\tL2\t\t\tSprint";
		std::string ps3controls3 = "\n\n\tSquare\t\tReload weapon\n\tTriangle\t\tToggle Turret mode\n\tX\t\t\tSpawn turret (in Turret Mode)\n\n";
		
		//string_var = pscontrols1 + pscontrols2;
		
		pFont->Draw(ps3controls1.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 255, 0, 0 });
		pFont->Draw(ps3controls2.c_str(), { left_start, starting_y + (newline_offset * num_newlines) }, scale, { 255, 255, 255 });
		pFont->Draw(ps3controls3.c_str(), { left_start, starting_y + (newline_offset * (num_newlines + 4)) }, scale, { 255, 255, 255 });
		#pragma endregion
	}




	/*
	std::string objective	= "Objective:\n pppppp\n\n\n";
	std::string controls	= "Controls:\n\nW\t\tMove towards mouse\nS\t\tMove away from mouse\nA\t\tStrafe left\nS\t\tStrafe right\n\n";
	std::string skills		= "Space\tToggle Active Camo\n\n\n";
	
	std::string output = objective + controls + skills;

	pFont->Draw(output.c_str(), { left_start, starting_y }, 0.8f, { 0, 255, 0 });
	*/
}
