#include "pch.h"
#include "PlayerController.h"
#include "InputManager.h"

void PlayerController::Update()
{
	//inputDirection = 0;

	if (InputManager::GetInstance()->GetButtonDown(KeyType::Z))
	{
		currentInput = KeyType::Z;
	}

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::Shift))
	{
		currentInput = KeyType::Shift;
	}

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::SpaceBar))
	{
		currentInput = KeyType::SpaceBar;
	}

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::Left))
	{
		currentInput = KeyType::Left;

	}

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::Right))
	{
		currentInput = KeyType::Right;

	}

	//else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Left) || InputManager::GetInstance()->GetButtonPressed(KeyType::Right))
	//{
	//	currentInput = KeyType::Move;

	//	/*if (InputManager::GetInstance()->GetButtonDown(KeyType::Left))
	//		inputDirection = -1;

	//	else
	//		inputDirection = 1;*/
	//}
	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Left))
	{
		currentInput = KeyType::KeepLeft;

	}
	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Right))
	{
		currentInput = KeyType::KeepRight;

	}

	else if (InputManager::GetInstance()->GetButtonUp(KeyType::Right) || InputManager::GetInstance()->GetButtonUp(KeyType::Left))
	{
		currentInput = KeyType::RELEASE;
	}

	else
	{
		currentInput = KeyType::MAX;
	}
}
