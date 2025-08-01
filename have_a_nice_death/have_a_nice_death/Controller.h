#pragma once
#include "InputManager.h"

class LivingObject;

class Controller
{
public:
	Controller() {}
	virtual ~Controller() {}

	virtual void Update();
	void SetOwner(LivingObject* owner) { _ownerLivingObject = owner; }
	LivingObject* GetOwner(void) { return _ownerLivingObject; }
	
protected:
	KeyType _currentInput;
	LivingObject* _ownerLivingObject = nullptr;
};

