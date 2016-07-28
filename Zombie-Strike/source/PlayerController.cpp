#include "PlayerController.h"
#include "MovingObject.h"
#include "Weapon.h"
#include "..\SGD Wrappers\SGD_InputManager.h"
#include "DestroyObjectMessage.h"
#include "Player.h"
#include "Game.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "GameplayState.h"
#include "HTPGameState.h"
#include "../SGD Wrappers/SGD_Handle.h"
#include "../SGD Wrappers/SGD_AudioManager.h"

#include "WeaponManager.h"


PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

/*virtual*/ bool PlayerController::Update(float dt, MovingObject* toUpdate, SGD::Point wayPoint)
{
	Player* m_Player = dynamic_cast<Player*>(toUpdate);

	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	/*
	if (pInput->IsControllerConnected(0) == true)
	{
		/*if (pInput->GetRightJoystick(0).x != 0.0f || pInput->GetRightJoystick(0).y != 0.0f)
		{
			SGD::Point	mpoint = pInput->GetMousePosition();
			SGD::Vector	joystick = pInput->GetLeftJoystick(0);
			float		stickmin = 0.250f;
			float		mousevel = 1.0f;


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
		}*/
		if (pInput->GetRightJoystick(0).x != 0 || pInput->GetRightJoystick(0).y != 0)
		{
			SGD::Vector toCursor;
			// rotate to face mouse
			if (Game::GetInstance()->GetCurrState() == HTPGameState::GetInstance())
				toCursor = SGD::Point(pInput->GetRightJoystick(0).x * 1000.0f + HTPGameState::GetInstance()->GetCamera()->GetPosition().x, pInput->GetRightJoystick(0).y * 1000.0f + HTPGameState::GetInstance()->GetCamera()->GetPosition().y) - toUpdate->GetPosition();
			else
				toCursor = SGD::Point(pInput->GetRightJoystick(0).x * 1000.0f + GameplayState::GetInstance()->GetCamera()->GetPosition().x, pInput->GetRightJoystick(0).y * 1000.0f + GameplayState::GetInstance()->GetCamera()->GetPosition().y) - toUpdate->GetPosition();

			if (m_Player->m_bIsAlive == true)
			{
				toCursor.Normalize();
				if (toCursor.ComputeDotProduct(toUpdate->GetDirection()) < 0.999f)
				{
					if (toUpdate->GetDirection().ComputeSteering(toCursor) > 0)
						toUpdate->SetRotation(toUpdate->GetRotation() + (SGD::PI*2.0f  * dt)); //Turn left

					else if (toUpdate->GetDirection().ComputeSteering(toCursor) < 0)
						toUpdate->SetRotation(toUpdate->GetRotation() - (SGD::PI*2.0f  * dt)); //Turn right

					SGD::Vector orientation = { 0, -1 };
					orientation.Rotate(toUpdate->GetRotation());
					toUpdate->SetDirection(orientation);

				}
			}
		}
			
	
	
	else
	{
		SGD::Vector toMouse;
		// rotate to face mouse
		if (Game::GetInstance()->GetCurrState() == HTPGameState::GetInstance())
			toMouse = SGD::Point(pInput->GetMousePosition().x + HTPGameState::GetInstance()->GetCamera()->GetPosition().x, pInput->GetMousePosition().y + HTPGameState::GetInstance()->GetCamera()->GetPosition().y) - toUpdate->GetPosition();
		else
			toMouse = SGD::Point(pInput->GetMousePosition().x + GameplayState::GetInstance()->GetCamera()->GetPosition().x, pInput->GetMousePosition().y + GameplayState::GetInstance()->GetCamera()->GetPosition().y) - toUpdate->GetPosition();

		
		if (m_Player->m_bIsAlive == true)
		{
			toMouse.Normalize();
			if (toMouse.ComputeDotProduct(toUpdate->GetDirection()) < 0.999f)
			{
				if (toUpdate->GetDirection().ComputeSteering(toMouse) > 0)
					toUpdate->SetRotation(toUpdate->GetRotation() + (SGD::PI*2.0f  * dt)); //Turn left

				else if (toUpdate->GetDirection().ComputeSteering(toMouse) < 0)
					toUpdate->SetRotation(toUpdate->GetRotation() - (SGD::PI*2.0f  * dt)); //Turn right

				SGD::Vector orientation = { 0, -1 };
				orientation.Rotate(toUpdate->GetRotation());
				toUpdate->SetDirection(orientation);
			}
		}

	}
	


	SGD::Point	mousepoint	= pInput->GetMousePosition();
	SGD::Point	camerapos	= Game::GetInstance()->GetCurrState() == HTPGameState::GetInstance()
		? HTPGameState::GetInstance()->GetCamera()->GetPosition()
		: GameplayState::GetInstance()->GetCamera()->GetPosition();
	if (pInput->IsControllerConnected(0) == true)
	{
		SGD::Vector	joystick = pInput->GetRightJoystick(0);

		if (joystick.x != 0.0f || joystick.y != 0.0f)
		{
			float		stickmin = 0.0f;
			float		mousevel = 20.0f;
			//float		maxdistance = 500.0f;

			if (joystick.x > stickmin)
				mousepoint.x += mousevel;
			else if (joystick.x < stickmin * -1.0f)
				mousepoint.x -= mousevel;

			if (joystick.y > stickmin)
				mousepoint.y += mousevel;
			else if (joystick.y < stickmin * -1.0f)
				mousepoint.y -= mousevel;

			if (mousepoint.x < 0.0F)
				mousepoint.x = 0.0F;
			if (mousepoint.y < 0.0F)
				mousepoint.y = 0.0F;
			if (mousepoint.x > Game::GetInstance()->GetScreenWidth())
				mousepoint.x = Game::GetInstance()->GetScreenWidth();
			if (mousepoint.y > Game::GetInstance()->GetScreenHeight())
				mousepoint.y = Game::GetInstance()->GetScreenHeight();

			pInput->SetMousePosition(mousepoint);
		}
	}

	SGD::Vector toMouse = SGD::Point(mousepoint.x + camerapos.x, mousepoint.y + camerapos.y) - toUpdate->GetPosition();
	if (m_Player->m_bIsAlive == true)
	{
		toMouse.Normalize();
		if (toMouse.ComputeDotProduct(toUpdate->GetDirection()) < 0.999f)
		{
			if (toUpdate->GetDirection().ComputeSteering(toMouse) > 0)
				toUpdate->SetRotation(toUpdate->GetRotation() + (SGD::PI *2.0f  * dt)); //Turn left

			else if (toUpdate->GetDirection().ComputeSteering(toMouse) < 0)
				toUpdate->SetRotation(toUpdate->GetRotation() - (SGD::PI *2.0f  * dt)); //Turn right

			SGD::Vector orientation = { 0, -1 };
			orientation.Rotate(toUpdate->GetRotation());
			toUpdate->SetDirection(orientation);
		}
	}


	std::string animation = "";
	//animation = m_Player->m_bIsAlive == true ? m_Player->animation.m_strCurrAnimation : "playerDeath";
	if (m_Player->m_bIsAlive == true)
	{
		//animation = m_Player->animation.m_strCurrAnimation;
		animation = WeaponManager::GetInstance()->GetSelected()->GetWeaponAnimType();
	}
	else
	{
		animation = "playerDeath";
	}



	// player is walking(playerWalk) OR running(playerRun)
	if ((pInput->IsKeyDown(SGD::Key::Shift) == true || pInput->IsButtonDown(0, 6) == true)  && m_Player->m_bIsAlive == true)
		m_Player->m_bIsSprinting = true;
	else if ((pInput->IsKeyDown(SGD::Key::Shift) == false || pInput->IsButtonDown(0, 6) == false) && m_Player->m_bIsAlive == true)
		m_Player->m_bIsSprinting = false;



	SGD::Vector newVelocity = { 0, 0 };


	// player moves forward/backward
	if ((pInput->IsKeyDown(SGD::Key::W) == true || pInput->GetLeftJoystick(0).y < 0) && m_Player->m_bIsAlive == true)
	{
		newVelocity += {0, -1};
		m_Player->m_bMoving = true;
	}
	if ((pInput->IsKeyDown(SGD::Key::S) == true || pInput->GetLeftJoystick(0).y > 0) && m_Player->m_bIsAlive == true)
	{
		newVelocity += {0, 1};
		m_Player->m_bMoving = true;
	}


	// player strafes left/right
	if ((pInput->IsKeyDown(SGD::Key::A) == true || pInput->GetLeftJoystick(0).x < 0) && m_Player->m_bIsAlive == true)
	{
		newVelocity += {-1, 0};
		m_Player->m_bMoving = true;
	}
	if ((pInput->IsKeyDown(SGD::Key::D) == true || pInput->GetLeftJoystick(0).x > 0) && m_Player->m_bIsAlive == true)
	{	
		newVelocity += {1, 0};
		m_Player->m_bMoving = true;
	}



	 if (pInput->IsControllerConnected(0) == true)
	 {
		 if (pInput->GetLeftJoystick(0).y == 0 && pInput->GetLeftJoystick(0).x == 0)
		 {
			 //animation = "playerIdle";
			 m_Player->m_bMoving = false;
		 } 
	 }
	 else
	 {
		 // player not moving
		 if ((pInput->IsKeyDown(SGD::Key::W) == false && pInput->IsKeyDown(SGD::Key::A) == false && pInput->IsKeyDown(SGD::Key::S) == false && pInput->IsKeyDown(SGD::Key::D) == false))
		 {
			 //animation = "playerIdle";
			 m_Player->m_bMoving = false;
		 }

	 }
	
	if (m_Player->IsSprinting() == true)
		m_Player->SetVelocity(newVelocity * m_Player->GetMoveSpeed() * 2);
	else
		m_Player->SetVelocity(newVelocity * m_Player->GetMoveSpeed());

	
	WeaponManager* pWeaponManager = WeaponManager::GetInstance();

	// selecting abilities
	if (pInput->IsKeyPressed(SGD::Key::N1) == true)
		pWeaponManager->SelectWeapon(PISTOL);
	else if (pInput->IsKeyPressed(SGD::Key::N2) == true)
		pWeaponManager->SelectWeapon(SHOTGUN);
	else if(pInput->IsKeyPressed(SGD::Key::N3) == true)
		pWeaponManager->SelectWeapon(SMG);
	else if (pInput->IsKeyPressed(SGD::Key::N4) == true)
		pWeaponManager->SelectWeapon(ASSUALT_RIFLE);
	else if (pInput->IsKeyPressed(SGD::Key::N5) == true)
		pWeaponManager->SelectWeapon(SPECIAL);


	
	//m_Player->flameThrower->Fire(dt);
	if (m_Player->isPlacingTurret() == false)
	{
		if (pWeaponManager->GetSelected()->GetAutomatic())
		{
			if ((pInput->IsKeyDown(SGD::Key::MouseLeft) == true) || (pInput->IsButtonDown(0, 7) == true))
				pWeaponManager->GetSelected()->Fire(dt);
		}
		else
		{
			if ((pInput->IsKeyPressed(SGD::Key::MouseLeft) == true) || (pInput->IsButtonPressed(0, 7) == true))
				pWeaponManager->GetSelected()->Fire(dt);
		}


		if ((pInput->IsKeyPressed(SGD::Key::R) == true || (pInput->IsButtonPressed(0, 0) == true)) && pWeaponManager->GetSelected()->IsReloading() == false)
			pWeaponManager->GetSelected()->ReloadNeeded();
	}
	else
	{
		if ((pInput->IsKeyPressed(SGD::Key::MouseLeft) == true) || (pInput->IsButtonPressed(0, 1) == true))
			m_Player->SpawnTurret();
	}

		


	// spawning turrets
	if (pInput->IsKeyPressed(SGD::Key::T) == true || (pInput->IsButtonPressed(0, 3) == true))
		m_Player->SetIsPlacingTurret(!m_Player->isPlacingTurret());
	



	// not sure
	if (pInput->IsKeyPressed(SGD::Key::N) == true)
	{
		m_Player->hud.nofiticationBar.isActive = !m_Player->hud.nofiticationBar.isActive;
	}




	


	// player not doing anything (playerIdle)
	if (m_Player->m_bMoving == false)
	{
		m_Player->SetVelocity({ 0, 0 });
	//	animation = "playerIdle";
		m_Player->m_bMoving = false;
	}



	//animation = pWeaponManager->GetSelected()->GetWeaponAnimType();
	if (m_Player->m_bIsAlive == true)
	{
		if (m_Player->m_bMoving == true)
		{
			m_Player->m_bIsSprinting == true
				? animation += "Run"
				: animation += "Walk";
		}
		else
		{
			animation += "Idle";
		}
	}
	else
	{
		animation = "playerDeath";
	}



	if (m_Player->GetAnimation() != animation)
	{
		m_Player->SetAnimation(animation);
	}
	


	return true;
	// nuh nuh
}
