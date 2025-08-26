#include "pch.h"
#include "PlayerController.h"
#include "InputManager.h"

void PlayerController::Update(float deltatime)
{
	//inputDirection = 0;

	pastInput = currentInput;

	if (InputManager::GetInstance()->GetButtonDown(KeyType::AttackKey1))
	{
		currentInput = KeyType::AttackKey1;
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

	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Up))
	{
		currentInput = KeyType::KeepUp;

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

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::AttackKey2))
	{
		currentInput = KeyType::AttackKey2;
	}

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::AttackKey3))
	{
		currentInput = KeyType::AttackKey3;
	}

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::AttackKey4))
	{
		currentInput = KeyType::AttackKey4;
	}

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::AttackKey5))
	{
		currentInput = KeyType::AttackKey5;
	}

	else if (InputManager::GetInstance()->GetButtonDown(KeyType::AttackKey6))
	{
		currentInput = KeyType::AttackKey6;
	}

	else
	{
		currentInput = KeyType::MAX;
	}
}
