#pragma once
#include "InputManager.h"
#include "LivingObject.h"

class LivingObject;

class Controller
{
public:
	Controller() {}
	virtual ~Controller() {}

	virtual void Update();
	void SetOwner(LivingObject* owner) { owningLivingObject = owner;}
	LivingObject* GetOwner(void) { return owningLivingObject; }

	KeyType GetInput() { return currentInput; }
	bool isPlayerController = false;
	
	int GetInputPressedX()
	{
		if (currentInput == KeyType::KeepRight)
			return 1;

		else if (currentInput == KeyType::KeepLeft)
			return -1;

		else
			return 0;
	}

	int GetPastInputPressedX()
	{
		if (pastInput == KeyType::KeepRight)
			return 1;

		else if (pastInput == KeyType::KeepLeft)
			return -1;

		else
			return 0;
	}

	int GetPastInputPressedY()
	{
		if (pastInput == KeyType::KeepUp)
			return 1;

		else
			return 0;
	}

	int GetInputDownX()
	{
		if (currentInput == KeyType::Right)
			return 1;

		else if (currentInput == KeyType::Left)
			return -1;

		else
			return 0;
	}

	KeyType GetPastInput() { return pastInput; }

protected:
	KeyType currentInput;
	KeyType pastInput = KeyType::MAX;
	LivingObject* owningLivingObject = nullptr;
};

