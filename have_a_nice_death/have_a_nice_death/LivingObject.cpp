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

void LivingObject::SetDebugMode(bool debugmode)
{
	for (auto& Iter : *ownTextures)
	{
		for (auto& iter : Iter.second)
		{
			iter->SetDrawBound(debugmode);
		}
	}
}

void LivingObject::SetState(std::string state, bool IsLoop)
{
	if (ownTextures->find(state) == ownTextures->end())
		return;

	SetAnimaotrTextures(&(*ownTextures)[state], IsLoop);
}
