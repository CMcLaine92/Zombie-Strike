#pragma once


#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_Handle.h"			// uses HTexture & HAudio
#include "Game.h"
#include <string>

class Player;

struct NotificationBar
{
	SGD::Rectangle textBar = { 0, 0, Game::GetInstance()->GetScreenWidth(), 0 };
	std::string text;
	float maxHeight = 128.0f;
	bool isActive = false;
};

class HUD
{
	SGD::HTexture	m_hBackgroundImage	= SGD::INVALID_HANDLE;

	Player*			m_pPlayer			= nullptr;

public:
	NotificationBar nofiticationBar;

	void Initialize(Player* player);
	void Shutdown();

	void Update(float dt);
	void Render(void);



	


};
