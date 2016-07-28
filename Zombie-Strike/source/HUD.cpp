#include "HUD.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_String.h"
#include "Player.h"
#include "BitmapFont.h"
#include <sstream>
using std::stringstream;

void HUD::Initialize(Player* player)
{
	SGD::GraphicsManager*	pGraphics = SGD::GraphicsManager::GetInstance();

	m_pPlayer = player;

	// Load assets
	//m_hBackgroundImage = pGraphics->LoadTexture("resource/graphics/HUD_clear3.png");
}
void HUD::Shutdown(void)
{
	SGD::GraphicsManager* pGraphics	= SGD::GraphicsManager::GetInstance();

	// Unload assets
	//pGraphics->UnloadTexture(m_hBackgroundImage);
}


void HUD::Update(float dt)
{
	if (nofiticationBar.isActive == true)
	{
		if (nofiticationBar.textBar.bottom < nofiticationBar.maxHeight) //if its active, open it up
			nofiticationBar.textBar.bottom += nofiticationBar.maxHeight * dt;
		if (nofiticationBar.textBar.bottom > nofiticationBar.maxHeight) // cap it off
			nofiticationBar.textBar.bottom = nofiticationBar.maxHeight;
	}
	else
	{
		if (nofiticationBar.textBar.bottom > 0) //if its active, open it up
			nofiticationBar.textBar.bottom -= nofiticationBar.maxHeight * dt;
		if (nofiticationBar.textBar.bottom < 0) // cap it off
			nofiticationBar.textBar.bottom = 0;
	}
}
void HUD::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	const BitmapFont* pFont = Game::GetInstance()->GetFont();


	// Draw the HUD image
	float	screenheight	= Game::GetInstance()->GetScreenHeight();

	//pGraphics->DrawTextureSection(m_hBackgroundImage, { 1.5f, screenheight - 112.0f }, SGD::Rectangle(4.0f, 694.0f, 708.0f, 806.0f));
	//pGraphics->DrawTexture(m_hBackgroundImage, { 1.5f, screenheight - 112.0f });


	// draw health bars
	SGD::Rectangle currhealth	= { 0, 0, m_pPlayer->GetCurrHealth() / m_pPlayer->GetMaxHealth() * 200, 35 };
	SGD::Rectangle maxhealth	= { 0, 0, 200, 35 };

	pGraphics->DrawRectangle(maxhealth, { 0, 0, 255 });

	SGD::Color healthcolor;
	if (m_pPlayer->GetCurrHealth() == m_pPlayer->GetMaxHealth())				// 100 -> Green
		healthcolor = { 0, 255, 0 };

	else if (m_pPlayer->GetCurrHealth() <= m_pPlayer->GetMaxHealth() * 0.5F)	// 0 - 25 -> Red
		healthcolor = { 255, 0, 0 };

	else																		// 25 - 99 -> yellow
		healthcolor = { 255, 255, 0 };

	pGraphics->DrawRectangle(currhealth, healthcolor);


	// draw health as a string
	int hp = static_cast<int>(m_pPlayer->GetCurrHealth());

	stringstream health;
	health << "HP: " << hp;
	pFont->Draw(health.str().c_str(), { 0, 0 }, 1.0f, { 255, 0, 255 });


}