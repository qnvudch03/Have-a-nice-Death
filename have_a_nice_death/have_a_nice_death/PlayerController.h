#pragma once
#include "Controller.h"
#include "InputManager.h"
class PlayerController : public Controller
{
public:
	PlayerController()
	{
		isPlayerController = true;
	}
	virtual void Update() override;
};

