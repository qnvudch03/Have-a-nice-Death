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
	
protected:
	KeyType currentInput;
	KeyType pastInput = KeyType::MAX;
	LivingObject* owningLivingObject = nullptr;
	//int inputDirection = 0;
};

