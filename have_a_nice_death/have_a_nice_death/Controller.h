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
	
protected:
	KeyType currentInput;
	LivingObject* owningLivingObject = nullptr;
	int inputDirection = 0;
};

