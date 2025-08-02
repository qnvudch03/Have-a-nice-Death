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

	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Left))
	{
		currentInput = KeyType::Left;
	}

	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Right))
	{
		currentInput = KeyType::Right;
	}

	else
	{
		currentInput = KeyType::MAX;
	}
}
