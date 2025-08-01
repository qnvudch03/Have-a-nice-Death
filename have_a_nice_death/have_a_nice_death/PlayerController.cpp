#include "pch.h"
#include "PlayerController.h"
#include "InputManager.h"

void PlayerController::Update()
{
	if (InputManager::GetInstance()->GetButtonDown(KeyType::Z))
	{
		_currentInput = KeyType::Z;
	}

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::Shift))
	{
		_currentInput = KeyType::Shift;
	}

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::SpaceBar))
	{
		_currentInput = KeyType::SpaceBar;
	}

	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Left))
	{
		_currentInput = KeyType::Left;
	}

	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Right))
	{
		_currentInput = KeyType::Right;
	}

	else
	{
		_currentInput = KeyType::MAX;
	}
}
