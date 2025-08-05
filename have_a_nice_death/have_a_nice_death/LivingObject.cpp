#include "pch.h"
#include "LivingObject.h"
#include "Controller.h"

//void LivingObject::Init()
//{
//	Super::Init();
//}
//
//void LivingObject::Update(float deltaTime)
//{
//	Super::Update(deltaTime);
//}

void LivingObject::Init()
{
	Super::Init();
}

void LivingObject::Update(float deltaTime)
{
	if (_controller != nullptr)
		_controller->Update();



	Super::Update(deltaTime);
}

void LivingObject::Destroy()
{
	Super::Destroy();
}

void LivingObject::SetState(std::string state, bool IsLoop)
{
	if (_ownTextures->find(state) == _ownTextures->end())
		return;

	SetAnimaotrTextures(&(*_ownTextures)[state], IsLoop);
}
