#include "pch.h"
#include "PlayerController.h"
#include "InputManager.h"

void PlayerController::Update()
{
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

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::Left) || InputManager::GetInstance()->GetButtonDown(KeyType::Right))
	{
		currentInput = KeyType::StartMove;
	}

	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Left) || InputManager::GetInstance()->GetButtonPressed(KeyType::Right))
	{
		currentInput = KeyType::Move;
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
